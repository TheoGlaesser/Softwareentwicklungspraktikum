#ifndef ASSEMBLER
#define ASSEMBLER
#include "Assembler.h"
#include "Element.h"
#include "linearAlgebra.h"
#include <cmath>
#endif

#define _USE_MATH_DEFINES
#include <cmath>


Assembler::Assembler() {
	dim = 2;
	n = 0;
}

//Initialize all class members, parameters just in read mode
Assembler::Assembler(const int & dim, const int & n, const std::vector<Backend::Node> & nodes, const std::vector<Backend::Rod> & rods, const std::vector<Backend::Force> & forces, const std::vector<Backend::Bearing> & bearings) : dim(dim),  n(n), nodes(nodes), rods(rods), forces(forces), bearings(bearings) {
	std::vector<std::vector<double>> zero_stiff(dim*n, std::vector<double> (dim*n,0));
	A = zero_stiff;
	std::vector<double> zero_disp(dim*n,0);
	displacement = zero_disp;
	std::vector<double> zero_rhs(dim*n, 0);
	rhs = zero_rhs;
};

//Functions to get the class variables
std::vector<std::vector<double>> Assembler::get_A() {return A;}
std::vector<double> Assembler::get_rhs() {return rhs;}
std::vector<double> Assembler::get_displacement() {return displacement;}

//Assembles and solves the system, i.e. for Ax = b, first A and b are built, and then it is solved for x
void Assembler::assemble(const double & E, const double & A_0) {
	//for each rod the local stiffness matrix is computed through the objects Element and then it is added accordingly to the global stiffness matrix 
	std::vector<std::vector<double>> stiff;
	for (int i = 0; i < rods.size(); i++) {
		double x_A = rods[i].p1.x;
		double y_A = rods[i].p1.y;
		double x_B = rods[i].p2.x;
		double y_B = rods[i].p2.y;
		Backend::Point p_A(x_A, y_A);
		Backend::Point p_B(x_B, y_B);
		Element my_fin_elem(p_A, p_B, nodes);
		//Compute local stiffness matrix
		stiff = my_fin_elem.compute_stiff(E, A_0);
		//Assign rods nodes to rods
		const Backend::Node* first_node_p = my_fin_elem.get_first_node();
		const Backend::Node* second_node_p = my_fin_elem.get_second_node();
		int first_node = (*first_node_p).id;
		int second_node =(*second_node_p).id;
		rods[i].first_node = first_node_p;
		rods[i].second_node = second_node_p;
		//Add to global stiffness matrix (make it better?)
		A[first_node*2][first_node*2] += stiff[0][0];
		A[first_node*2][first_node*2 + 1] += stiff[0][1];
		A[first_node*2 + 1][first_node*2] += stiff[1][0];
		A[first_node*2 + 1][first_node*2 +1] += stiff[1][1];
		A[first_node*2][second_node*2] += stiff[0][2];
		A[first_node*2][second_node*2 + 1] += stiff[0][3];
		A[first_node*2 + 1][second_node*2] += stiff[1][2];
		A[first_node*2 + 1][second_node*2 + 1] += stiff[1][3];
		A[second_node*2][first_node*2] += stiff[2][0];
		A[second_node*2][first_node*2 + 1] += stiff[2][1];
		A[second_node*2 + 1][first_node*2] += stiff[3][0];
		A[second_node*2 + 1][first_node*2 + 1] += stiff[3][1];
		A[second_node*2][second_node*2] += stiff[2][2];
		A[second_node*2][second_node*2 + 1] += stiff[2][3];
		A[second_node*2 + 1][second_node*2] += stiff[3][2];
		A[second_node*2 + 1][second_node*2 + 1] += stiff[3][3];
		
	}

	//Compute right hand side of system, i.e. the b vector
	rhs = compute_forces();

	//Consider bearings
	apply_bearings();

	//compute the new nodes after solving the linear system and considering the displacements
	new_nodes = solve();

	//compute new rods
	new_rods = compute_new_rods();

	/*std::cout << "The new nodes are: " << std::endl;
	for (int i = 0; i < new_nodes.size(); i++) {
		new_nodes[i].print();
	}
	*/

}

//computes the force vector (right hand side)
std::vector<double> Assembler::compute_forces() {
	//assign to the forces the corresponding nodes (make it better?)
	for (int i = 0; i < forces.size(); i++) {
		for (int j = 0; j < nodes.size(); j++) {
			if (forces[i].p.x == nodes[j].p.x && forces[i].p.y == nodes[j].p.y) {
				forces[i].node_p = &nodes[j];
				break;
			}
		}
	}
	
	std::vector<double> force_truss(dim*n, 0);
	for (int i = 0; i < forces.size(); i++) {
		int node_id = (*forces[i].node_p).id;
		int index = dim*node_id;
		//Convert from deg to rad
		double rad = forces[i].angle*M_PI/180;
		double norm = forces[i].norm;
		//Write in the force vector the corresponding load
		force_truss[index] = std::cos(rad)*norm;
		force_truss[index + 1] = std::sin(rad)*norm;
	}

	return force_truss;
}

//Consider bearings in the stiffness matrix
void Assembler::apply_bearings() {
	//Maybe to be improved, also bearings is not constant
	//Assign bearing to node
	for (int i = 0; i < bearings.size(); i++) {
	       for (int j = 0; j < nodes.size(); j++) {
	 		if (bearings[i].p.x == nodes[j].p.x && bearings[i].p.y == nodes[j].p.y) {
			  	bearings[i].node_p = &nodes[j];
		  	  	break;
			}		
	       } 
	}
	
	//Compute correction term in the right hand side of system
	for (int i = 0; i < bearings.size(); i++) {
		std::vector<double> correction(dim*n, 0);
		//Find the nodes of the bearings
		Backend::Node* node_x_p = bearings[i].node_p;
		int node_x = ((*node_x_p).id)*2;
		int node_y = ((*node_x_p).id)*2 + 1;
		for (int j = 0; j < correction.size(); j+=2) {
			//skip if node corresponds to bearing
			if (j == node_x || j == node_y) {
				continue;
			}
			//add to correction term the first boundary condition times the correspondin value in the stiffness matrix
			correction[j] += bearings[i].bound_condition_x*A[j][node_x];
			correction[j+1] += bearings[i].bound_condition_y*A[j+1][node_y];
		}
		
		
		//Apply boundary conditions to right hand side
		rhs[node_x] = bearings[i].bound_condition_x;
		rhs[node_y] = bearings[i].bound_condition_y;
		
		//Apply the correction to right hand side
		for (int k = 0; k < correction.size(); k++) {
			//skip the indexes referring to the bearing nodes
			if (k == node_x || k == node_y) {
				continue;
			}
			rhs[k] -= correction[k];
		}

		//modify stiffness matrix accordingly: coloumn zeros
		for (int j = 0; j < A.size(); j++) {
                        A[j][node_x] = 0;
                        A[j][node_y] = 0;
                }
		
		//modify stiffness matrix accordingly: row zeros
		std::vector<double> mod_row(dim*n, 0);
		mod_row[node_x] = 1;
		A[node_x] = mod_row;
                
		std::vector<double> mod_row_next(dim*n, 0);
		mod_row_next[node_y] = 1;
                A[node_y] = mod_row_next;

	}		

}

//Solve the linear system with eigen
std::vector<Backend::Node> Assembler::solve() {
	//Convert forces to eigen
	Eigen::VectorXd eigen_rhs(n*dim);
	for (int i = 0; i < eigen_rhs.size(); i++) {
		eigen_rhs(i) = rhs[i];
	}

	//Convert stiffness matrix to eigen
	Eigen::MatrixXd eigen_A(n*dim, n*dim);
       	for (int i = 0; i < n*dim; i++) {
		for (int j = 0; j < n*dim; j++) {
			eigen_A(i,j) = A[i][j];	
		}
	}
	
	//Solve the system with llt decomposition
	Eigen::VectorXd eigen_x = eigen_A.llt().solve(eigen_rhs);
	
	//Save the values in the displacement variable
	for (int i = 0; i < n*dim; i++) {
		displacement[i] = eigen_x(i);
	}
	
	//compute the new nodes by taking into consideration the displacement
	std::vector<Backend::Node> new_nodes_local(nodes.size());
	new_nodes_local = nodes;
	for (int i = 0; i < new_nodes_local.size(); i++) {
		new_nodes_local[i].p.x += displacement[dim*i];
		new_nodes_local[i].p.y += displacement[dim*i + 1];
	}

	return new_nodes_local;

}

//Compute the rods after the system has been solved
std::vector<Backend::Rod> Assembler::compute_new_rods() {
	std::vector<Backend::Rod> new_rods((rods).size());
	for (int i = 0; i < new_rods.size(); i++) {
		int first_node = (*rods[i].first_node).id;
		int second_node = (*rods[i].second_node).id;
		new_rods[i].first_node = &new_nodes[first_node];
		new_rods[i].second_node = &new_nodes[second_node];
		new_rods[i].p1.x = new_nodes[first_node].p.x;
		new_rods[i].p1.y = new_nodes[first_node].p.y;
		new_rods[i].p2.x = new_nodes[second_node].p.x;
		new_rods[i].p2.y = new_nodes[second_node].p.y;
	}

	return new_rods;

}


//In the following int main () function there is an implementation that checks if everything is working. If you compile it now it might not work because of the Makefiles. Anyway, the same correctness check is written in the test, so please run the test to check for correctness.
/*
int main() {
	Backend::Node Node1(0,0,0);
	Backend::Node Node2(0,2,1);
	Backend::Node Node3(2,2,2);
	Backend::Node Node4(2,0,3);
	Backend::Node Node5(1,4,4);
	std::vector<Backend::Node> nodes = {Node1, Node2, Node3, Node4, Node5};
	Backend::Rod Rod1(0,0,0,2);
	Backend::Rod Rod2(0,2,2,2);
	Backend::Rod Rod3(2,2,2,0);
	Backend::Rod Rod4(2,0,0,2);
	Backend::Rod Rod5(0,2,1,4);
	Backend::Rod Rod6(1,4,2,2);
	Backend::Rod Rod7(2,2,0,0);
	Backend::Rod Rod8(0,0,2,0);
	std::vector<Backend::Rod> rods = {Rod1, Rod2, Rod3, Rod4, Rod5, Rod6, Rod7, Rod8};
	Backend::Force Force1(2,2,-10,45);
	Backend::Force Force2(1,4,-30,90);
	//Backend::Force Force3(2,0,-70,30);
	std::vector<Backend::Force> forces = {Force1, Force2};
	Backend::Bearing Bearing1(0,0,0,0);
	Backend::Bearing Bearing2(2,0,0,0);
	std::vector<Backend::Bearing> bearings = {Bearing1, Bearing2};
	Assembler truss(2, nodes.size(), nodes,rods, forces, bearings);
	std::cout << "truss has been built" << std::endl;
	truss.assemble(1,1);
	std::vector<std::vector<double>> A = truss.get_A();
	std::cout << "A was built" << std::endl;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A.size(); j++) {
			std::cout << A[i][j] << " ";
		}
		std::cout << std::endl;
	}

	
	std::vector<double> truss_forces = truss.get_rhs();
	std::cout << "The vector of forces is: ";
	for (int i = 0; i < truss_forces.size(); i++) {
		std::cout << truss_forces[i] << " ";
	}
	std::cout << std::endl;
	std::vector<double> truss_displacement = truss.get_displacement();
	std::cout << "The displacements are: ";
	for (int i = 0; i < truss_displacement.size(); i++) {
		std::cout << truss_displacement[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
*/

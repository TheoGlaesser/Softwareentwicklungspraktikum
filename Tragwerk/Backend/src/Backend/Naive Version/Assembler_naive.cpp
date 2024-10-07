#include "Assembler_naive.h"
#include "Element_naive.cpp"
#include "linearAlgebra_naive.h"
#include <cmath>

#define _USE_MATH_DEFINES
#include <cmath>

Assembler::Assembler(const int & dim, const int & n ) : dim(dim),  n(n) {
	std::vector<std::vector<double>> zero_stiff(dim*n, std::vector<double> (dim*n,0));
	A = zero_stiff;
	std::vector<double> zero_disp(dim*n,0);
	displacement = zero_disp;
	std::vector<double> zero_forces(dim*n, 0);
	forces = zero_forces;
};

std::vector<std::vector<double>> Assembler::get_A() {return A;}
std::vector<double> Assembler::get_forces() {return forces;}
std::vector<double> Assembler::get_displacement() {return displacement;}


void Assembler::assemble(const std::vector<Backend::Node> & nodes, std::vector<Backend::Rod> & rods, std::vector<Backend::Force> & ext_forces, std::vector<Backend::Bearing> & bearings, const double & E, const double & A_0) {
	std::vector<std::vector<double>> stiff;
	for (int i = 0; i < rods.size(); i++) {
		double x_A = rods[i].p1.x;
		double y_A = rods[i].p1.y;
		double x_B = rods[i].p2.x;
		double y_B = rods[i].p2.y;
		Element my_fin_elem(x_A, y_A, x_B, y_B);
		stiff = my_fin_elem.compute_stiff(E, A_0);
		my_fin_elem.assign_nodes(nodes);
		int first_node = my_fin_elem.get_first_node();
		int second_node = my_fin_elem.get_second_node();
		rods[i].first_node = first_node;
		rods[i].second_node = second_node;
		//make it better?
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
		
		//to check the iterations
		/*for (int i = 0; i < A.size(); i++) {
	                for (int j = 0; j < A.size(); j++) {
        	                std::cout << A[i][j] << " ";
                	}
                	std::cout << std::endl;
        	}

		std::cout << std::endl;
		*/
		
	}
	
	forces = compute_forces(ext_forces, nodes);
	apply_bearings(nodes, bearings);
	new_nodes = solve(nodes);
	std::cout << "The new nodes are: " << std::endl;
	for (int i = 0; i < new_nodes.size(); i++) {
		new_nodes[i].print();
	}

}


std::vector<double> Assembler::compute_forces(std::vector<Backend::Force> & forces, const std::vector<Backend::Node> & nodes) {
	//Maybe to be improved, also forces is not const
	for (int i = 0; i < forces.size(); i++) {
		for (int j = 0; j < nodes.size(); j++) {
			if (forces[i].p.x == nodes[j].p.x && forces[i].p.y == nodes[j].p.y) {
				forces[i].node_id = nodes[j].id;
				break;
			}
		}
	}
	
	std::vector<double> force_truss(dim*n, 0);
	for (int i = 0; i < forces.size(); i++) {
		int index = 2*forces[i].node_id;
		double rad = forces[i].angle*M_PI/180;
		double norm = forces[i].norm;
		force_truss[index] = std::cos(rad)*norm;
		force_truss[index + 1] = std::sin(rad)*norm;
	}

	return force_truss;
}


void Assembler::apply_bearings(const std::vector<Backend::Node> & nodes, std::vector<Backend::Bearing> & bearings) {
	//Maybe to be improved, also bearings is not constant
	//Assign bearing to node
	for (int i = 0; i < bearings.size(); i++) {
	       for (int j = 0; j < nodes.size(); j++) {
	 		if (bearings[i].p.x == nodes[j].p.x && bearings[i].p.y == nodes[j].p.y) {
			  	bearings[i].node_id = nodes[j].id;
		  	  	break;
			}		
	       } 
	}
	
	//Compute correction term in the right hand side of system
	for (int i = 0; i < bearings.size(); i++) {
		std::vector<double> correction(dim*n, 0);
		int node_x = bearings[i].node_id*2;
		int node_y = bearings[i].node_id*2 + 1;
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
		forces[node_x] = bearings[i].bound_condition_x;
		forces[node_y] = bearings[i].bound_condition_y;
		
		//Apply the correction to right hand side
		for (int k = 0; k < correction.size(); k++) {
			//skip the indexes referring to the bearing nodes
			if (k == node_x || k == node_y) {
				continue;
			}
			forces[k] -= correction[k];
		}

		//modify accordingly stiffness matrix: coloumn zeros
		for (int j = 0; j < A.size(); j++) {
                        A[j][node_x] = 0;
                        A[j][node_y] = 0;
                }
		
		//modify accordingly stiffnes matrix: row zeros
		std::vector<double> mod_row(dim*n, 0);
		mod_row[node_x] = 1;
		A[node_x] = mod_row;
                
		std::vector<double> mod_row_next(dim*n, 0);
		mod_row_next[node_y] = 1;
                A[node_y] = mod_row_next;

	}		

}

std::vector<Backend::Node> Assembler::solve(const std::vector<Backend::Node> & nodes) {
	//Convert forces to eigen
	Eigen::VectorXd eigen_forces(n*dim);
	for (int i = 0; i < eigen_forces.size(); i++) {
		eigen_forces(i) = forces[i];
	}

	//Convert stiffness matrix to eigen
	Eigen::MatrixXd eigen_A(n*dim, n*dim);
       	for (int i = 0; i < n*dim; i++) {
		for (int j = 0; j < n*dim; j++) {
			eigen_A(i,j) = A[i][j];	
		}
	}
	
	//Solve the system with llt decomposition
	Eigen::VectorXd eigen_x = eigen_A.llt().solve(eigen_forces);
	
	//Save the values in the displacement variable
	for (int i = 0; i < n*dim; i++) {
		displacement[i] = eigen_x(i);
	}
	
	//compute the new nodes by taking into consideration the displacement
	std::vector<Backend::Node> new_nodes_local(nodes.size());
	for (int i = 0; i < new_nodes_local.size(); i++) {
		new_nodes_local[i].p.x += displacement[dim*i];
		new_nodes_local[i].p.y += displacement[dim*i + 1];
	}

	return new_nodes_local;

}

std::vector<Backend::Rod> get_new_rods(const std::vector<Backend::Node> & new_nodes, const std::vector<Backend::Rod> & old_rods) {
	std::vector<Backend::Rod> new_rods(old_rods.size());
	for (int i = 0; i < new_rods.size(); i++) {
		int first_node = old_rods[i].first_node;
		int second_node = old_rods[i].second_node;
		new_rods[i].p1.x = new_nodes[first_node].p.x;
		new_rods[i].p1.y = new_nodes[first_node].p.y;
		new_rods[i].p2.x = new_nodes[second_node].p.x;
		new_rods[i].p2.y = new_nodes[second_node].p.y;
		new_rods[i].first_node = first_node;
		new_rods[i].second_node = second_node;
	}

	return new_rods;

}

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
	Backend::Bearing Bearing1(0,0,0,-2);
	Backend::Bearing Bearing2(2,0,0,-2);
	std::vector<Backend::Bearing> bearings = {Bearing1, Bearing2};
	Assembler truss(2, nodes.size());
	std::cout << "truss has been built" << std::endl;
	truss.assemble(nodes, rods, forces, bearings,1,1);
	std::vector<std::vector<double>> A = truss.get_A();
	/*std::cout << "A was built" << std::endl;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A.size(); j++) {
			std::cout << A[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::vector<double> truss_forces = truss.get_forces();
	std::cout << "The vector of forces is: ";
	for (int i = 0; i < truss_forces.size(); i++) {
		std::cout << truss_forces[i] << " ";
	}
	std::cout << std::endl;
	*/
	std::vector<double> truss_displacement = truss.get_displacement();
	std::cout << "The displacements are: ";
	for (int i = 0; i < truss_displacement.size(); i++) {
		std::cout << truss_displacement[i] << " ";
	}
	std::cout << std::endl;


	return 0;
}



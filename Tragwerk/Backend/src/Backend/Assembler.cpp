#ifndef ASSEMBLER
#define ASSEMBLER
#include "Assembler.h"
#include "Element.h"
#include "linearAlgebra.h"
#include <cmath>
#include <utility>
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
std::vector<Backend::Node> Assembler::get_new_nodes() {return new_nodes;}
std::vector<Backend::Rod> Assembler::get_new_rods() {return new_rods;}
std::vector<Backend::Force> Assembler::get_new_forces() {return new_forces;}
std::vector<Backend::Bearing> Assembler::get_new_bearings() {return new_bearings;}

//Assembles and solves the system, i.e. for Ax = b, first A and b are built, and then it is solved for x
void Assembler::assemble(const double & E, const double & A_0, Backend::Exception & error) {
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
		if (my_fin_elem.get_first_node() == nullptr || my_fin_elem.get_second_node() == nullptr) {
			error.message = "System is not solvable";
			error.isVisible = false;
			return;
		}
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
	compute_rhs(error);
	
	//Consider bearings
	apply_bearings(error);

	//compute the new nodes after solving the linear system and considering the displacements
	new_nodes = solve(error);
	
	//compute new rods
	new_rods = compute_new_rods(error);
	
	//compute new bearings
	new_bearings = compute_new_bearings(error);

	//compute new forces
	new_forces = compute_new_forces(error);

}

//computes the force vector (right hand side)
void Assembler::compute_rhs(Backend::Exception & error) {
	
	//assign to the forces the corresponding nodes (make it better?)
	for (int i = 0; i < forces.size(); i++) {
		for (int j = 0; j < nodes.size(); j++) {
			if (forces[i].p.x == nodes[j].p.x && forces[i].p.y == nodes[j].p.y) {
				forces[i].node_p = &nodes[j];
				break;
			}
		}
	}

	for (int i = 0; i < forces.size(); i++) {
		if (forces[i].node_p == nullptr) {
			error.message = "System is not solvable";
			error.isVisible = false;
			return;
		}
	}
	
	std::vector<double> force_truss(dim*n, 0);
	for (int i = 0; i < forces.size(); i++) {
		int node_id = (*forces[i].node_p).id;
		int index = dim*node_id;
		double norm = forces[i].norm;
		double rad = forces[i].angle;
		//Write in the force vector the corresponding load
		force_truss[index] = -std::cos(rad)*norm;
		force_truss[index + 1] = -std::sin(rad)*norm;
	}
	rhs = force_truss;
}

//Consider bearings in the stiffness matrix
void Assembler::apply_bearings(Backend::Exception & error) {
	//Assign bearing to node
	for (int i = 0; i < bearings.size(); i++) {
		for (int j = 0; j < nodes.size(); j++) {
	 		if (bearings[i].p.x == nodes[j].p.x && bearings[i].p.y == nodes[j].p.y) {
			  	bearings[i].node_p = &nodes[j];
		  	  	break;
			}		
	       } 
	}
	
	for (int i = 0; i < bearings.size(); i++) {
		if (bearings[i].node_p == nullptr) {
			error.message = "System is not solvable";
			error.isVisible = false;
			return;
		}
	}

	//Compute correction term in the right hand side of system
	for (int i = 0; i < bearings.size(); i++) {
		std::vector<double> correction(dim*n, 0);
		//Find the nodes of the bearings
		Backend::Node* node_x_p = bearings[i].node_p;
		int node_x = ((*node_x_p).id)*2;
		int node_y = ((*node_x_p).id)*2 + 1;
		//Check that there is a boundary condition in x direction
		if (bearings[i].xInfo.first) {
			for (int j = 0; j < correction.size(); j+=2) {
				//skip if node corresponds to bearing
				if (j == node_x) {
					continue;
					}
				//add to correction term the first boundary condition times the corresponding value in the stiffness matrix
				correction[j] += bearings[i].xInfo.second*A[j][node_x];
				}
		}
		
		//Check that there is a boundary condition in y direction
		if (bearings[i].yInfo.first) {
                        for (int j = 0; j < correction.size(); j+=2) {
                                //skip if node corresponds to bearing
                                if (j == node_y) {
                                        continue;
                                        }
                                //add to correction term the second boundary condition times the corresponding value in the stiffness matrix
                                correction[j+1] += bearings[i].yInfo.second*A[j+1][node_y];
                                }
                }
		
		
		
		//Apply boundary conditions to right hand side
		if (bearings[i].xInfo.first) {
			rhs[node_x] = bearings[i].xInfo.second;
		}

		if (bearings[i].yInfo.second) {
			rhs[node_y] = bearings[i].yInfo.second;
		}
		
		//Apply the correction to right hand side
		for (int k = 0; k < correction.size(); k++) {
			//skip the indexes referring to the bearing nodes
			if (k == node_x || k == node_y) {
				continue;
			}
			rhs[k] -= correction[k];
		}

		//modify stiffness matrix - x direction
		if (bearings[i].xInfo.first) {
			//coloumn zeros
			for (int j = 0; j < A.size(); j++) {
                        	A[j][node_x] = 0;
			}
			//row zeros
			std::vector<double> mod_row(dim*n, 0);
                	mod_row[node_x] = 1;
                	A[node_x] = mod_row;
		}

		//modify stiffness matrix - y direction
		if (bearings[i].yInfo.first) {
			//coloumn zeros
			for (int j = 0; j < A.size(); j++) {
                        	A[j][node_y] = 0;
			}
			//row zeros
			std::vector<double> mod_row_next(dim*n, 0);
                	mod_row_next[node_y] = 1;
                	A[node_y] = mod_row_next;
                }
		

	}		

}

//Solve the linear system with eigen
std::vector<Backend::Node> Assembler::solve(Backend::Exception & error) {
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

	
	//Check that the matrix is invertible
	if (eigen_A.llt().info() == Eigen::NumericalIssue) {
		error.message = "Stiffness matrix is not invertible - system hasn't been solved. Please try with other truss.";
		error.isVisible = false;
		return nodes;
	}

	
	//Solve the system with llt decomposition
	Eigen::VectorXd eigen_x = eigen_A.llt().solve(eigen_rhs);

	//Save the values in the displacement variable
	for (int i = 0; i < n*dim; i++) {
		//Check that the displacements aren't infinite
		if (std::isnan(eigen_x(i))) {
			error.message = "System is unstable, please try with different truss";
			error.isVisible = false;
			return nodes;
		}

		displacement[i] = eigen_x(i);
	}
	
	//compute the new nodes by taking into consideration the displacement
	std::vector<Backend::Node> new_nodes_local = nodes;
	for (int i = 0; i < new_nodes_local.size(); i++) {
		new_nodes_local[i].p.x += displacement[dim*i];
		new_nodes_local[i].p.y += displacement[dim*i + 1];
		new_nodes_local[i].print();
		}

	return new_nodes_local;

}

//Compute the rods after the system has been solved
std::vector<Backend::Rod> Assembler::compute_new_rods(Backend::Exception & error) {
	std::vector<Backend::Rod> new_rods((rods).size());
	for (int i = 0; i < new_rods.size(); i++) {
		if (rods[i].first_node == nullptr || rods[i].second_node == nullptr) {
			error.message = "System is not solvable";
			error.isVisible = false;
			return rods;
		}
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


std::vector<Backend::Force> Assembler::compute_new_forces(Backend::Exception & error) {
	std::vector<Backend::Force> new_forces(forces.size());
   for(int i=0; i<forces.size(); i++) {
	   if (forces[i].node_p == nullptr) {
		   error.isVisible = false;
		   error.message = "System is not solvable";
		   return forces;
	   }
	   int node_p = (*forces[i].node_p).id;
	   new_forces[i].norm = forces[i].norm;
   	   new_forces[i].angle = forces[i].angle;
	   new_forces[i].p.x = new_nodes[node_p].p.x;
	   new_forces[i].p.y = new_nodes[node_p].p.y;
	   new_forces[i].node_p = &new_nodes[node_p];	   
   }
   return new_forces;
}

std::vector<Backend::Bearing> Assembler::compute_new_bearings(Backend::Exception & error) {
	std::vector<Backend::Bearing> new_bearings(bearings.size());
	for (int i=0; i < new_bearings.size(); i++) {
		if (bearings[i].node_p == nullptr) {
			error.isVisible = false;
			error.message = "System is not solvable";
			return bearings;
		}
		
		int node_p = (*bearings[i].node_p).id;
		new_bearings[i].p.x = new_nodes[node_p].p.x;
		new_bearings[i].p.y = new_nodes[node_p].p.y;
		std::cout << new_bearings[i].p.x << " " << new_bearings[i].p.y << std::endl;
		new_bearings[i].xInfo.first = 0;
		new_bearings[i].xInfo.second = 0;
		new_bearings[i].yInfo.first = 0;
                new_bearings[i].yInfo.second = 0;
	}
	return new_bearings;
}


//In the following int main () function there is an implementation that checks if everything is working. If you compile it now it might not work because of the Makefiles. Anyway, the same correctness check is written in the test, so please run the test to check for correctness.

/*
int main() {
	Backend::Node Node1(0,0,0);
	Backend::Node Node2(0,100,1);
	Backend::Node Node3(100,100,2);
	Backend::Node Node4(100,0,3);
	Backend::Node Node5(50,200,4);
	std::vector<Backend::Node> nodes = {Node1, Node2, Node3, Node4, Node5};
	Backend::Rod Rod1(0,0,0,100);
	Backend::Rod Rod2(0,100,100,100);
	Backend::Rod Rod3(100,100,100,0);
	Backend::Rod Rod4(100,0,0,100);
	Backend::Rod Rod5(0,100,50,200);
	Backend::Rod Rod6(50,200,100,100);
	Backend::Rod Rod7(100,100,0,0);
	Backend::Rod Rod8(0,0,100,0);
	std::vector<Backend::Rod> rods = {Rod1, Rod2, Rod3, Rod4, Rod5, Rod6, Rod7, Rod8};
	double angle = 90;
	double rad = angle*M_PI/180;
	Backend::Force Force1(50,200,100000,rad);
	//Backend::Force Force3(2,0,-70,30);
	std::vector<Backend::Force> forces = {Force1};
	std::pair<bool,double> xInfo1(false, 0);
	std::pair<bool,double> yInfo1(true, 0);
	Backend::Bearing Bearing1(0,0,xInfo1,yInfo1);
	std::pair<bool, double> xInfo2(true, 0);
	std::pair<bool, double> yInfo2(true, 0);
	Backend::Bearing Bearing2(100,0,xInfo2,yInfo2);
	std::vector<Backend::Bearing> bearings = {Bearing1, Bearing2};
	Assembler truss(2, nodes.size(), nodes,rods, forces, bearings);
	std::cout << "truss has been built" << std::endl;
	bool isVisible = true;
	Backend::Exception error(true);
	truss.assemble(100000,1,error);
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

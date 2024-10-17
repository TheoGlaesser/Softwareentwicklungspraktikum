#include <vector>
#include <iostream>
#include "Simulator.h"
#include "Assembler.h"
#include "Constants.h"

namespace Backend
{
  Simulator::Simulator(bool linear): islinear(linear) {}


  results Simulator::run(std::vector<Rod> rods, std::vector<Force> forces, std::vector<Bearing> bearings, std::vector<Node> nodes, const double &  E, const double & A_0) 
  {
	  std::cout << "Run has been entered" << std::endl;  
  	Assembler truss(Constants::NUM_DIMENSIONS, nodes.size(), nodes, rods, forces, bearings);
	std::cout << "TRuss has been built" << std::endl;  
	truss.assemble(E, A_0);
	std::cout << "Truss has been assembled" << std::endl;
	
    std::vector<Backend::Node> newNodes = truss.get_new_nodes();
    
    /*std::cout << "nodes are: "; 
    for (int i = 0; i < newNodes.size(); i++) {
	    nodes[i].print();
    }*/

    std::cout << "Truss has been solved" << std::endl;
		std::vector<Backend::Rod> newRods = truss.get_new_rods();

		std::vector<Backend::Force> newForces =  truss.get_new_forces();
   std::cout << "New rods and new forces have been computed" << std::endl;

    //Maybe store the values of the new nodes and rods in the Simulator variables
    std::cout << "Dimensions of vectors: " << newRods.size() << " "  << newForces.size() << " " << bearings.size() << newNodes.size() << std::endl; 
    results result(newRods, newForces, bearings, newNodes);
    return result;
  }
}




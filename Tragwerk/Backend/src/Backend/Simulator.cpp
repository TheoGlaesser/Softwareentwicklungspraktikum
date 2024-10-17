#include <vector>
#include <iostream>
#include "Simulator.h"
#include "Assembler.h"
#include "Constants.h"

namespace Backend
{
  Simulator::Simulator(bool linear): islinear(linear) {}


  results Simulator::run(std::vector<Rod> rods, std::vector<Force> forces, std::vector<Bearing> bearings, std::vector<Node> nodes, const double &  E, const double & A_0, bool& isVisible) 
  {
	
	for (int i = 0; i < nodes.size(); i ++) {
	       nodes[i].print();
	}	       
  	Assembler truss(Constants::NUM_DIMENSIONS, nodes.size(), nodes, rods, forces, bearings); 
	truss.assemble(E, A_0, isVisible);
    
	std::vector<Backend::Node> newNodes = truss.get_new_nodes();

    	std::vector<Backend::Rod> newRods = truss.get_new_rods();

<<<<<<< HEAD
		std::vector<Backend::Force> newForces =  truss.get_new_forces();
   std::cout << "New rods and new forces have been computed" << std::endl;

    //Maybe store the values of the new nodes and rods in the Simulator variables
    std::cout << "Dimensions of vectors: " << newRods.size() << " "  << newForces.size() << " " << bearings.size() << newNodes.size() << std::endl; 
    results result(newRods, newForces, bearings, newNodes);
=======
   	std::vector<Backend::Force> newForces =  truss.get_new_forces();
    
       	results result(newRods, newForces, bearings, newNodes);
>>>>>>> e613bc4d371f1dc3429e1d6f740cb9885d6e2f17
    return result;
  }
}




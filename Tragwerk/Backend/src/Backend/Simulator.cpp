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
  	Assembler truss(Constants::NUM_DIMENSIONS, nodes.size(), nodes, rods, forces, bearings);
	  truss.assemble(E, A_0);

    std::vector<Node> newNodes = truss.solve();
		std::vector<Rod> newRods = truss.compute_new_rods();
		std::vector<Backend::Force> newForces =  truss.compute_new_forces();
   
   
    //Maybe store the values of the new nodes and rods in the Simulator variables
    std::cout << "Hi Kevin" << std::endl;
    results result(newRods, newForces, bearings, newNodes);
    return result;
  }
}




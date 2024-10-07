#include <vector>
#include <iostream>
#include "Simulator.h"
#include "Assembler.h"
#include "Constants.h"

namespace Backend
{
  Simulator::Simulator(bool linear): islinear(linear) {}


  void Simulator::run(std::vector<Rod> & rods, const std::vector<Force> & forces, const std::vector<Bearing> & bearings, std::vector<Node> & nodes, const double &  E, const double & A_0) 
  {
    std::vector<Rod> copyOfRods = rods; std::vector<Force> copyOfForces = forces; std::vector<Bearing> copyOfBearings = bearings; std::vector<Node> copyOfNodes = nodes;
  	Assembler truss(Constants::NUM_DIMENSIONS, copyOfNodes.size(), copyOfNodes, copyOfRods, copyOfForces, copyOfBearings);
	  truss.assemble(E, A_0);

    std::vector<Node> newNodes = truss.solve();
		std::vector<Rod> newRods = truss.compute_new_rods();

    nodes = newNodes;
    rods = newRods;
	  //Maybe store the values of the new nodes and rods in the Simulator variables
  }
}




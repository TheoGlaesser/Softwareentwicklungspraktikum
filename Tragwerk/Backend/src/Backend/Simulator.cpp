#pragma once
#include <vector>
#include <iostream>
#include "Simulator.h"
#include "Assembler.h"
#include "Constants.h"

namespace Backend
{

  Simulator::Simulator(bool linear): islinear(linear) {}

  ///Runs the simulation, invoking the class Assembler
  results Simulator::run(std::vector<Rod> rods, std::vector<Force> forces, std::vector<Bearing> bearings, std::vector<Node> nodes, const double &  E, const double & A_0, Exception & error) 
  {
	
  	Assembler truss(Constants::NUM_DIMENSIONS, nodes.size(), nodes, rods, forces, bearings); 
	truss.assemble(E, A_0, error);
    
	std::vector<Backend::Node> newNodes = truss.get_new_nodes();

    	std::vector<Backend::Rod> newRods = truss.get_new_rods();

	std::vector<Backend::Force> newForces =  truss.get_new_forces();
	
	std::vector<Backend::Bearing> newBearings = truss.get_new_bearings();
	
	results result(newRods, newForces, newBearings, newNodes);
    return result;
  }
}




#include <vector>
#include <iostream>
#include "Simulator.h"
#include "Assembler.h"

namespace Backend
{

  Simulator::Simulator(bool linear): islinear(linear) {}



  void Simulator::run(const std::vector<Rod> & rods, const std::vector<Force> & forces, const std::vector<Bearing> & bearings,const std::vector<Node> & nodes, const double &  E, const double & A_0) {
  	  Assembler truss(2, nodes.size(),nodes, rods, forces, bearings);
	  truss.assemble(E, A_0);
	  //Maybe store the values of the new nodes and rods in the Simulator variables

  }
}

int main() {
	//Eventually run the simulator here
	std::cout << "Cmake is working" << std::endl;
	return 0;
}

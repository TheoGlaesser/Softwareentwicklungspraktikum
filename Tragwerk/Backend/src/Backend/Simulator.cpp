#include <vector>
#include <iostream>
#include "Simulator.h"
#include "linearAlgebra.h"

namespace Backend
{


  Simulator::Simulator(const std::vector<Rod> & rods, const std::vector<Force> & forces, const std::vector<Bearing> & bearing, bool linear) {
  std::cout << "Hello\n";
  }

  Simulator::~Simulator() {
  std::cout << "Bye\n";
  }

}

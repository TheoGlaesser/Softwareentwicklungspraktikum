#include <vector>
#include <iostream>
#include "Simulator.h"

namespace Backend
{


  Simulator::Simulator(const la::vector_t<Rod> & rods, const la::vector_t<Force> & forces, const la::vector_t<Bearing> & bearing, bool linear) {
  std::cout << "Hello\n";
  }

  Simulator::~Simulator() {
  std::cout << "Bye\n";
  }

}

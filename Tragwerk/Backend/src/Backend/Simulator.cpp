#include <vector>
#include <iostream>
#include "Simulator.h"

namespace Backend
{


  Simulator::Simulator(const std::vector<Rod> & rods, const std::vector<Force> & forces, const std::vector<Bearing> & bearing, bool linear, double E, double A) {
    std::cout << "Hello\n";
  }

  Simulator::~Simulator() {
  std::cout << "Bye\n";
  }



  Simulator::run() 
  {
    //TODO
  }
}







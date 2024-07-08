#pragma once
#include <vector>
#include <iostream>

namespace Backend {

  struct Point {
    double x, y;
  };

  struct Rod {
    Point p1;
    Point p2;
  };


  struct Force {
    Point p;
    double norm;
    double angle;
  };

  struct Bearing {
    Point p;
  };



  class Simulator {
    public:
      Simulator(const std::vector<Rod> & rods, const std::vector<Force> & forces, const std::vector<Bearing> & bearing, bool linear);
      ~Simulator();

      std::vector<Rod> run();
    private: 
      std::vector<Rod> rods;
      std::vector<Force> forces;
      std::vector<Bearing> bearing;
  };

}


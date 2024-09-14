#pragma once
#include "linearAlgebra.h"
#include <vector>
#include <iostream>

namespace Backend {

  struct Point {
    double x, y;

    Point() : x(0), y(0) {}
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
      Simulator(const la::vector_t<Rod> & rods, const la::vector_t<Force> & forces, const la::vector_t<Bearing> & bearing, bool linear);
      ~Simulator();

      la::vector_t<Rod> run();
    private: 
      la::vector_t<Rod> rods;
      la::vector_t<Force> forces;
      la::vector_t<Bearing> bearings;
  };

}


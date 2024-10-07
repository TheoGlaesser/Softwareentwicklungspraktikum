#pragma once
#include "linearAlgebra_naive.h"
#include <vector>
#include <iostream>

namespace Backend {

  struct Point {
    double x, y;

    Point() : x(0), y(0) {}
    Point(double x, double y): x(x), y(y) {}
  };

  struct Rod {
    Point p1;
    Point p2;
    int first_node=0;
    int second_node=0;

    Rod() : p1(0,0) , p2(0,0) {}
    Rod(double x1, double y1, double x2, double y2) : p1(x1,y1), p2(x2,y2) {}
  };

  struct Node {
	Point p;
	int id;
	Node() : p(0,0), id(0) {}
      	Node(double x, double y, int id) : p(x,y), id(id) {} 
	void print() {std::cout << "(" << p.x << "," << p.y << ")" << std::endl;}
};


  struct Force {
    Point p;
    double norm;
    double angle;
    int node_id = 0;

    Force() : p(0,0), norm(0), angle(0) {}
    Force(double x, double y, double norm, double angle) : p(x,y), norm(norm), angle(angle) {}
  };

  struct Bearing {
    Point p;
    int node_id = 0;
    double bound_condition_x;
    double bound_condition_y;
    Bearing() : p(0,0) {}
    Bearing(double x, double y, double bound_condition_x, double bound_condition_y) : p(x,y), bound_condition_x(bound_condition_x), bound_condition_y(bound_condition_y) {}
  };





class Simulator {
    public:
      Simulator(const std::vector<Rod> & rods, const std::vector<Force> & forces, const std::vector<Bearing> & bearing,const std::vector<Node> &nodes, bool linear, double E, double A);
      ~Simulator();

      std::vector<Rod> run();
    private: 
      std::vector<Rod> rods;
      std::vector<Force> forces;
      std::vector<Bearing> bearings;
      std::vector<Node> nodes;
  };

}


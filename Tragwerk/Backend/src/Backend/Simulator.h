#pragma once
#include "linearAlgebra.h"
#include "Constants.h"
#include <vector>
#include <iostream>

///Namespace including the necessary objects to correctly run the backend
namespace Backend {
 
  ///Class Point that represents a point on the grid	
  struct Point {
    double x, y;

    Point() : x(0), y(0) {}
    Point(double x, double y): x(x), y(y) {}
  };

  ///Class Node that represents a node on the grid
  struct Node {
	Point p;
	int id;
	Node() : p(0,0), id(0) {}
      	Node(double x, double y, int id) : p(x,y), id(id) {} 
	void print() {std::cout << "(" << p.x << "," << p.y << ")" << std::endl;}
};

   ///Class Rod that represents a rod on the grid   
  struct Rod {
    Point p1;
    Point p2;
    const Node* first_node=nullptr;
    const Node* second_node=nullptr;

    Rod() : p1(0,0) , p2(0,0) {}
    Rod(double x1, double y1, double x2, double y2) : p1(x1,y1), p2(x2,y2) {}
  };

  

 
   ///Class Force that represents a force on the grid 
  struct Force {
    Point p;
    double norm;
    double angle;
    const Node* node_p=nullptr;

    Force() : p(0,0), norm(0), angle(0) {}
    Force(double x, double y, double norm, double angle) : p(x,y), norm(norm), angle(angle) {}
  };
  
  
   ///Class Bearing that represents a support on the grid
  struct Bearing {
    Point p;
    Node* node_p = nullptr;
    std::pair<bool, double> xInfo;
    std::pair<bool, double> yInfo;
    Bearing() : p(0,0) {}
    Bearing(double x, double y, const std::pair<bool,double> xInfo, const std::pair<bool,double> yInfo) : p(x,y), xInfo(xInfo), yInfo(yInfo) {}
  };

 
  ///Class results that stores the values of the variables after the simulation 
  struct results {
    std::vector<Rod> rods;
    std::vector<Force> forces;
    std::vector<Bearing> bearings;
    std::vector<Node> nodes;

    results(std::vector<Rod> rods, std::vector<Force> forces, std::vector<Bearing> bearings, std::vector<Node> nodes): rods(rods), forces(forces), bearings(bearings), nodes(nodes) {}


    results() {};

  };

   /// Class Exception that contains a message and a boolean indicating if there has been an error during the simulation  
  struct Exception {
        bool isVisible;
        std::string message = "no error";
        Exception(const bool & isVisible): isVisible(isVisible) {}
};




///Class Simulator, that runs and manages the simulation and connects frontend to backend, and viceversa
class Simulator {
    public:
      Simulator(bool linear);
      ~Simulator() {};
      
      ///Runs the simulation invoking Assembler
      results run(std::vector<Rod>, std::vector<Force>, std::vector<Bearing>, std::vector<Node>, const double &, const double &, Exception &);
    private: 
      std::vector<Rod> rods;
      std::vector<Force> forces;
      std::vector<Bearing> bearings;
      std::vector<Node> nodes;
      bool islinear;
  };

}


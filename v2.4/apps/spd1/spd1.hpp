// info@stce.rwth-aachen.de
#pragma once
#include "cppNum/convexObjective/objective.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>



template<typename T> 
T co::objective_t::f(const la::vector_t<T> &x, const la::vector_t<T> &p) { 
  using namespace std;
  int N=x.size(); assert(N>1); assert(p.size()==N);
  static la::matrix_t<T> A(N,N);
  static bool loaded = false;
  T y=0;

  if(!loaded) 
  {
  	std::ifstream matrix("matrix.txt");
  	for(int i=0; i<N; i++) {
		  for(int j=0; j<N; j++) {
			  matrix >> A(i,j);
		  }
 	 }
	loaded = true;
  }


  for (int i=0;i<N;++i) {
	  for(int j=0; j<N; j++) {
		y += 0.5 * x(j) * A(j,i)  * x(i);
	  }
  }


  return y;
}

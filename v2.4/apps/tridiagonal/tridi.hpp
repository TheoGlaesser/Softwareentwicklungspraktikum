// info@stce.rwth-aachen.de
#pragma once
#include "cppNum/convexObjective/objective.hpp"
#include <cassert>
#include <cmath>
#include <iostream>




template<typename T> 
T co::objective_t::f(const la::vector_t<T> &x, const la::vector_t<T> &p) { 
  using namespace std;
  int n=x.size(); assert(n>1); assert(p.size()==n);
  static la::matrix_t<T> A(n,n); 
  T y=0;

  static bool once = true;
  if(once) { 
	once = false;

	A(0,0) = 2;
	
   	for(int i=1; i<n; i++) {
		A(i,i) = 2; 
		A(i,i-1) = -1;
		A(i-1,i) = -1;
	}
}
  

  for (int i=0;i<n;++i) {
	  for(int j=0; j<n; j++) {
		y += 0.5 * x(j) * A(j,i)  * x(i);
	  }
  }

  return y;
}

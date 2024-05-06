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
  T y=0;


  la::matrix_t<T> A(n,n); 

  for(int i=0; i<n; i++) {
  	for(int j=0; j<n; j++) {
		T val = 1.0/ (i+j+1.0);
		A(i,j) = val;
	}
  }

  for (int i=0;i<n;++i) {
	  for(int j=0; j<n; j++) {
		y += 0.5 * x(j) * A(j,i)  * x(i);
	  }
  }
  return y;
}

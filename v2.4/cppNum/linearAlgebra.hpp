// info@stce.rwth-aachen.de
#pragma once

#include "Eigen/Dense"
#include <iostream>
#include <cmath>

namespace la {

  template<typename T, int N=Eigen::Dynamic>
  using vector_t=Eigen::Matrix<T,N,1>;

  template<typename T, int M=Eigen::Dynamic, int N=M>
  using matrix_t=Eigen::Matrix<T,M,N>;

  template<typename T>
  struct lu_solver_t {
    static la::vector_t<T> run(const la::matrix_t<T>& A, const la::vector_t<T>& b) { 
      return A.lu().solve(b);
    }
  };

  template<typename T>
  struct llt_solver_t {
    static la::vector_t<T> run(const la::matrix_t<T>& A, const la::vector_t<T>& b) { 
      return A.llt().solve(b);
    }
  };
  
  template<typename T>
  struct gs_solver_t {
  static la::vector_t<T> run(const la::matrix_t<T>& A, const la::vector_t<T>& b) {
	int n = b.size();
	la::vector_t<T> x(n), x_prev(n);
	T error = 5, tol = 0.0000001;


	while (error > tol) {
		for(int i=0; i<n; i++) {
			T temp1 = 0, temp2 = 0;

			for(int j=0; j<i; j++) {
				temp1 = temp1 + A(i,j) * x(j);
			}
			for(int j=i+1; j<n; j++) {
				temp2 = temp2 + A(i,j) * x_prev(j);
			}


			x(i) = (1/A(i,i)) * (b(i) - temp1 - temp2);
		}

		for(int i=0; i<n; i++) {
			if(abs(x(i) - x_prev(i)) < error) {error = abs(x(i) - x_prev(i));}	
			x_prev(i) = x(i);
		}
	}
	return x;
     }
  };



}

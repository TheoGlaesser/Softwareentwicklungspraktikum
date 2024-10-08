// info@stce.rwth-aachen.de
#pragma once

#include "../../../thirdParty/eigen-3.4.0/Eigen/Dense"
#include <iostream>
#include <cmath>

//The namespace stores the different algorithms used to solve linear systems.
namespace Backend {
namespace la {

  template<typename T, int N=Eigen::Dynamic>
  using vector_t=Eigen::Matrix<T,N,1>;

  template<typename T, int M=Eigen::Dynamic, int N=M>
  using matrix_t=Eigen::Matrix<T,M,N>;


///This is the lower and upper decomposition - not iterative
  template<typename T>
  struct lu_solver_t {
    static la::vector_t<T> run(const la::matrix_t<T>& A, const la::vector_t<T>& b) { 
      return A.lu().solve(b);
    }
  };


///This is the cholesky decomposition (llt) - not iterative
  template<typename T>
  struct llt_solver_t {
    static la::vector_t<T> run(const la::matrix_t<T>& A, const la::vector_t<T>& b) { 
      return A.llt().solve(b);
    }
  };
  

  ///This is the iterative solver using the gauss-seidel method
  template<typename T>
  struct gs_solver_t {
  static la::vector_t<T> run(const la::matrix_t<T>& A, const la::vector_t<T>& b) {
	int n = b.size(), iterations = 0, max_iterations = 2000;
	la::vector_t<T> x(n), x_prev(n);
	T error = 5, tol = 1e-15;

	while (abs(error) > tol && iterations++ < max_iterations)  {
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

}


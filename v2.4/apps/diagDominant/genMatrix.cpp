// info@stce.rwth-aachen.de
#include "../../../thirdParty/eigen-3.4.0/Eigen/Dense"
#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>


template<typename T, int M=Eigen::Dynamic, int N=M>
using matrix_t=Eigen::Matrix<T,M,N>;

int main(int argc, char* argv[]) 
{
	//Dmension of generated matrix
	assert(argc == 2);
	int N=std::stoi(argv[1]);

	static matrix_t<double> A(N,N);
	for (int i = 0; i < N; i++) {
  		for (int j = 0; j < N; j++) {
			A(i,j) =((double) std::rand() / (RAND_MAX));
       		 }
 	 }

	 static  matrix_t<double> B = (0.5*(A  + A.transpose()));

	  for (int i = 0; i < N; i ++) {
       		 B(i, i) += N/2;
 	 }

	std::ofstream matrix("matrix.txt");
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			matrix << B(i,j) << " ";
		}
		matrix << "\n";
	}

	matrix.close();


	 return 0;
}

#include <iostream>
#include <eigen3/Eigen/Dense>


//These functions create a random spd matrix. The fact that 0.5(A + A^T) is symmetric and a strong diagonal 
//is used to create the matrix. There are two functions: the first one uses MatrixXd which allows to create 
//bigger matrices. The second one uses the normal eigen matrix, but it can't create matrices with bigger 
//dimensions.

Eigen::MatrixXd random_spd_big(const int n) {
	Eigen::MatrixXd A(n,n);
	for (int i = 1; i < n; i++) {
                for (int j = 1; j < n; j++) {
                        A(i,j) =((double) std::rand() / (RAND_MAX));
                }
        }
	
	Eigen::MatrixXd B = 0.5*(A  + A.transpose());
	
	for (int i = 0; i < n; i ++) {
                B(i, i) += n;
        }

	return B;
}

template<typename T, int N=Eigen::Dynamic>
Eigen::Matrix<T,N,N> random_spd_small() {
	Eigen::Matrix<T,N,N> A;
        for (int i = 1; i < N; i++) {
                for (int j = 1; j < N; j++) {
                        A(i,j) =((double) std::rand() / (RAND_MAX));
                }
        }

        Eigen::Matrix<T,N,N> B = 0.5*(A  + A.transpose());

        for (int i = 0; i < N; i ++) {
                B(i, i) += N;
        }

        return B;
}



int main() {
	const int n = 100;
	Eigen::MatrixXd B = random_spd_big(n);
	Eigen::Matrix<double,n,n> C = random_spd_small<double,n>();

	/* To print the matrix
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << C(i,j) << " ";
		}
		std::cout << std::endl;
	}
	*/

	

	
	for (int i = 0; i < n; i ++) {
		B(i, i) += n;
	}
	
	Eigen::LLT<Eigen::MatrixXd> lltOfA(B);
	if (lltOfA.info() == Eigen::NumericalIssue) {
		std::cout << "False" << std::endl;
	}
	bool my_bool = B.llt().info() == Eigen::Success;
	std::cout << my_bool << std::endl;
	bool my_bool_C = C.llt().info() == Eigen::Success;
	std::cout << my_bool_C << std::endl;
	return 0;
}

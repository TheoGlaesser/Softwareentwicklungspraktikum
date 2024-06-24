// info@stce.rwth-aachen.de
#include "apps/tridiagonal/tridi.hpp"
#include "cppNum/convexObjective/newton.hpp"
#include "cppNum/linearAlgebra.hpp"
#include "cppNum/derivative.hpp"
#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>

int main(int argc, char* argv[]) {
  //runtime 

  auto start = std::chrono::high_resolution_clock::now();
  //
  using T=double;
  using namespace std;
  assert(argc==2);
  int np=std::stoi(argv[1]), nx=np; 
  la::vector_t<T> p=la::vector_t<T>::Random(np); 
  la::vector_t<T> x=la::vector_t<T>::Random(nx); 

  co::newton_minimizer_t<T, la::gs_solver_t<T>> minimizer(1e-7);
  x=minimizer.run(x,p);
  cout << "x=" << x.transpose() << "\nf(x)=" << co::objective_t::f(x,p) << endl
    << "||dfdx||=" << derivative_t::dfdx<co::objective_t>(x,p).norm() << endl
    << "spd(ddfdxx)=" << !(derivative_t::ddfdxx<co::objective_t>(x,p).llt().info()) << endl;

  auto stop = std::chrono::high_resolution_clock::now();
  std::cout << "runtime: " <<  std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() << "\n";

  return 0;
}  

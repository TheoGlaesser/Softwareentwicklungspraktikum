// info@stce.rwth-aachen.de
#include "apps/equations/g1.hpp"
#include "cppNum/differentialEquation/implicitEuler.hpp"
#include <vector>
#include <iostream>

int main() {
  using T=double;
  T p=0.5, x=1, t_target=1; int number_of_timesteps=100;
  // enable tracing
  bool trace=true;
  de::implicitEuler_integrator_t<T> integrator(t_target,number_of_timesteps,trace);
  // record trace
  x=integrator.run(x,p);
  // write trace to file
  integrator.plot("implicitEuler_steps.plt");
  std::cout << "x=" << x << std::endl;
  return 0;
}  

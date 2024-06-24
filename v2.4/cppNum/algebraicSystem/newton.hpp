// info@stce.rwth-aachen.de
#pragma once

#include "system.hpp"
#include "solver.hpp"

namespace as {
///It inherites from solver_t and it receives as well as template parameter a solver, using as default one the llt_solver. It allows to run the solver with the routine run, which is inherited from solver_t and then it is called by newton_minimizer_t
  template<typename T, typename SYSTEM_T=system_t, typename LINEAR_SOLVER_T = la::llt_solver_t<T>>
  class newton_solver_t : public solver_t<T,SYSTEM_T> {
      using solver_t<T,SYSTEM_T>::_states;
      using solver_t<T,SYSTEM_T>::_parameters;
      using solver_t<T,SYSTEM_T>::_accuracy;
      using solver_t<T,SYSTEM_T>::_trace;
    public:
      newton_solver_t(const T& accuray, bool trace=false);
      la::vector_t<T> run(la::vector_t<T> x, const la::vector_t<T>& p);
  };

}

#include "cppNum/derivative.hpp"

namespace as {
  template<typename T, typename SYSTEM_T, typename LINEAR_SOLVER_T>
  newton_solver_t<T,SYSTEM_T,LINEAR_SOLVER_T>::newton_solver_t(const T& accuracy,bool trace) : solver_t<T,SYSTEM_T>(accuracy,trace) {}
///this function receives as template parameter the solver the users wants to use and then runs the newton method, solving the linear system using the solver.If none specified, the default one will be used. 
  template<typename T, typename SYSTEM_T, typename LINEAR_SOLVER_T>
  la::vector_t<T> newton_solver_t<T,SYSTEM_T,LINEAR_SOLVER_T>::run(la::vector_t<T> x, const la::vector_t<T> &p) {
    if (_trace) { _states.push_back(x); _parameters=p; }
    la::vector_t<T> residual=SYSTEM_T::F(x,p);
    do {
      x+=LINEAR_SOLVER_T::run(derivative_t::dFdx<SYSTEM_T,T>(x,p),-residual);
      if (_trace) _states.push_back(x);
      residual=SYSTEM_T::F(x,p);
    } while (residual.norm()>_accuracy);
    return x;
  }

}

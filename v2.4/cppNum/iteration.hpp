// info@stce.rwth-aachen.de
#pragma once

#include "linearAlgebra.hpp"
#include <vector>
#include <string>

///This abstract class allows to store parameters, states and a bool for the trace. It then allows to plot the results.
template<typename T>
class iteration_t {
  protected:
    la::vector_t<T> _parameters;
    std::vector<la::vector_t<T>> _states;
    bool _trace;
  public:
    iteration_t(bool trace);
    const std::vector<la::vector_t<T>>& get_states() const;
    virtual void plot(const std::string& filename, int i) const=0;
    virtual void plot(const std::string& filename, int i, int j) const=0;
};

template<typename T>
iteration_t<T>::iteration_t(bool trace) : _trace(trace) {}

template<typename T>
const std::vector<la::vector_t<T>>& iteration_t<T>::get_states() const { return _states; }

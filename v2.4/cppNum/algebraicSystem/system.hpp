// info@stce.rwth-aachen.de
#pragma once

#include "cppNum/linearAlgebra.hpp"

namespace as {
///This class is representing a function that returns a vector, in our case it represents the derivative of the function we want to minimize.
  struct system_t {
    template<typename T>
    static la::vector_t<T> F(const la::vector_t<T>& x, const la::vector_t<T>& p);
  };

}

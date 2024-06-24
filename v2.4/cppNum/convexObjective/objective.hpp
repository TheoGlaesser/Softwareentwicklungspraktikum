// info@stce.rwth-aachen.de
#pragma once

#include "cppNum/linearAlgebra.hpp"

namespace co {
///this struct stores the function to minimize.
  struct objective_t {
    template <typename T>
    static T f(const la::vector_t<T>& x, const la::vector_t<T>& p);
  };

}

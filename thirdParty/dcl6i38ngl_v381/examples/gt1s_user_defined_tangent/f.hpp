/**
dco/c++ v3.8.1
    -- Algorithmic Differentiation by Operator Overloading in C++

COPYRIGHT 2022
The Numerical Algorithms Group Limited and
Software and Tools for Computational Engineering @ RWTH Aachen University

This file is part of dco/c++.
**/

#include "g.hpp"

template <class T> void f(T p, T& x) {
  p = exp(p);
  g(p, x);
  x = x * p;
}
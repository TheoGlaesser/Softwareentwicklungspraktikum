/**
dco/c++ v3.8.1
    -- Algorithmic Differentiation by Operator Overloading in C++

COPYRIGHT 2022
The Numerical Algorithms Group Limited and
Software and Tools for Computational Engineering @ RWTH Aachen University

This file is part of dco/c++.
**/

#include <cstdlib>
#include <iostream>
#include <cassert>
#include "dco.hpp"
using namespace std;
using namespace dco;
typedef gt1s<double>::type DCO_BASE_TYPE;
typedef ga1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;
typedef DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

#include "../include/f.hpp"

template <typename DCO_MODE, typename TYPE> void Solve_make_gap(const vector<TYPE>& LU, vector<TYPE>& b);

void EulerSteps(const size_t m, const vector<DCO_TYPE>& A, vector<DCO_TYPE>& T) {
  size_t n = T.size();
  for (size_t j = 0; j < m; j++) {
    for (size_t i = 0; i < n; ++i)
      T[i] = -T[i];
    if (dco::tape(A)->is_active())
      Solve_make_gap<DCO_MODE>(A, T);
    else
      Solve(A, T);
  }
}

template <typename DCO_TYPE> void EulerSteps_make_gap(const size_t m, const vector<DCO_TYPE>& A, vector<DCO_TYPE>& T) {
  size_t n = T.size();

  auto T_in(T);

  // forward run
  dco::tape(A)->switch_to_passive();
  EulerSteps(m, A, T);
  dco::tape(A)->switch_to_active();

  // register output
  for (size_t i = 0; i < n; i++)
    dco::tape(A)->register_variable(T[i]);

  auto fill_gap = [=, &A]() {
    auto p = dco::tape(A)->get_position();
    vector<DCO_TYPE> Tl(T_in);

    // forward run
    EulerSteps(m, A, Tl);
    cerr << "record =" << dco::size_of(dco::tape(A)) << "B" << endl;

    // get output adjoints (seeds for this section)
    for (size_t i = 0; i < n; i++) {
      dco::tape(A)->register_output_variable(Tl[i]);
      dco::derivative(Tl[i]) = dco::derivative(T[i]);
    }

    // reverse run and reset to position p (so only reverse run of Solve)
    dco::tape(A)->interpret_adjoint_and_reset_to(p);
  };

  dco::tape(A)->insert_callback(std::move(fill_gap));
}

template <typename DCO_MODE, typename TYPE> void LUDecomp_make_gap(vector<TYPE>& A) {
  size_t n = sqrt(double(A.size()));
  vector<DCO_BASE_TYPE> Ap(n * n);
  for (size_t i = 0; i < n * n; i++)
    Ap[i] = value(A[i]);
  LUDecomp(Ap);
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++)
      value(A[i * n + j]) = Ap[i * n + j];
}

// U^T*y=b
template <class TYPE> inline void FSubstT(const vector<TYPE>& LU, vector<TYPE>& y) {
  size_t n = y.size();
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < i; j++)
      y[i] = y[i] - LU[j * n + i] * y[j];
    y[i] = y[i] / LU[i * n + i];
  }
}

// L^T*x=y
template <class TYPE> inline void BSubstT(const vector<TYPE>& LU, vector<TYPE>& b) {
  size_t n = b.size();
  for (size_t k = n, i = n - 1; k > 0; k--, i--)
    for (size_t j = n - 1; j > i; j--)
      b[i] = b[i] - LU[j * n + i] * b[j];
}

// LU^T*x=y
template <class TYPE> inline void SolveT(const vector<TYPE>& LU, vector<TYPE>& b) {
  FSubstT(LU, b);
  BSubstT(LU, b);
}

template <typename DCO_MODE, typename TYPE> void Solve_make_gap(const vector<TYPE>& LU, vector<TYPE>& b) {
  const size_t n = b.size();
  auto rhs(b);
  dco::tape(LU)->switch_to_passive();
  Solve(LU, b);
  dco::tape(LU)->switch_to_active();
  dco::tape(LU)->register_variable(b);

  auto fill_gap = [=, &LU]() {
    vector<DCO_TYPE> a1b(n);
    for (size_t i = 0; i < n; ++i)
      a1b[i] = dco::derivative(b[i]);
    dco::tape(LU)->switch_to_passive();
    SolveT(LU, a1b);

    for (size_t i = 0; i < n; i++)
      for (size_t j = 0; j < n; j++)
        dco::derivative(LU[i * n + j]) += dco::value(-a1b[i] * b[j]);
    dco::derivative(rhs) += dco::value(a1b);
    dco::tape(LU)->switch_to_active();
  };

  dco::tape(LU)->insert_callback(std::move(fill_gap));
}

inline void sim(const vector<DCO_TYPE>& c, const size_t m, vector<DCO_TYPE>& T, const size_t cs) {
  const size_t n = c.size();
  static vector<DCO_TYPE> A(n * n);
  residual_jacobian(c, T, A);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j)
      A[i * n + j] = A[i * n + j] / m;
    A[i + i * n] = A[i + i * n] - 1;
  }
  LUDecomp_make_gap<DCO_MODE>(A);
  for (size_t j = 0; j < m; j += cs) {
    size_t s = (j + cs < m) ? cs : m - j;
    EulerSteps_make_gap<DCO_TYPE>(s, A, T);
  }
}

template <typename TYPE, typename OTYPE>
inline void f(const vector<TYPE>& c, const size_t m, vector<TYPE>& T, const vector<OTYPE>& O, TYPE& v,
              const size_t cs) {
  sim(c, m, T, cs);
  v = 0;
  size_t n = T.size();
  for (size_t i = 0; i < n - 1; ++i)
    v = v + (T[i] - O[i]) * (T[i] - O[i]);
  v = v / (n - 1);
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    cerr << "3 parameters expected:" << endl
         << "  1. number of spatial finite difference grid points" << endl
         << "  2. number of implicit Euler steps" << endl
         << "  3. distance between checkpoints" << endl;
    return EXIT_FAILURE;
  }
  size_t n = atoi(argv[1]), m = atoi(argv[2]), cs = atoi(argv[3]);
  assert(cs <= m);
  vector<double> c(n);
  for (size_t i = 0; i < n; i++)
    c[i] = 0.01;
  vector<double> T(n);
  for (size_t i = 0; i < n - 1; i++)
    T[i] = 300.;
  T[n - 1] = 1700.;
  ifstream ifs("O.txt");
  vector<double> O(n);
  for (size_t i = 0; i < n; i++)
    ifs >> O[i];
  vector<vector<double>> d2vdc2(n, vector<double>(n, 0));
  vector<DCO_TYPE> ca(n);
  vector<DCO_TYPE> Ta(n);
  DCO_TYPE va;

  dco::smart_tape_ptr_t<DCO_MODE> tape;
  for (size_t i = 0; i < n; i++) {
    ca[i] = c[i];
    Ta[i] = T[i];
    tape->register_variable(ca[i]);
  }
  DCO_TAPE_POSITION_TYPE p = tape->get_position();
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++)
      Ta[j] = T[j];
    if (i > 0)
      tape->zero_adjoints();
    derivative(value(ca[i])) = 1;
    f(ca, m, Ta, O, va, cs);
    value(derivative(va)) = 1;
    tape->interpret_adjoint();
    for (size_t j = 0; j < n; j++)
      derivative(value(ca[j])) = 0;
    for (size_t j = 0; j < n; j++)
      d2vdc2[j][i] = derivative(derivative(ca[j]));
    tape->reset_to(p);
  }
  cout.precision(5);
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++)
      cout << "d2vdc2[" << i << "][" << j << "]=" << d2vdc2[i][j] << endl;
}

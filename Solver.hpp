#include "Matrix.hpp"

#ifndef GAUSS_SOLVER_H
#define GAUSS_SOLVER_H

class Solver {
public:
    Matrix mtx;
    Solver(Matrix m) : mtx(m){}
    virtual Matrix solve() = 0;
    Matrix solve_and_print_time();
};

#endif
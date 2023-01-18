#include "Solver.hpp"

#ifndef GAUSS_CLASSIC_SOLVER_H
#define GAUSS_CLASSIC_SOLVER_H

class ClassicSolver : public Solver {
public:
    // Standard constructor.
    ClassicSolver(Matrix m) : Solver(m) {}

    // Implementation of the method of the parent class solve.
    Matrix solve() override;
};

#endif
#include "Solver.hpp"

#ifndef GAUSS_PARALLEL_SOLVER_H
#define GAUSS_PARALLEL_SOLVER_H

class ParallelSolver : public Solver {
public:
    // Standard constructor.
    ParallelSolver(Matrix m) : Solver(m) {}

    // Implementation of the method of the parent class solve.
    Matrix solve() override;
};

#endif

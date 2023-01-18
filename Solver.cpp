#include "Solver.hpp"

Matrix Solver::solve_and_print_time(){
    auto start = std::chrono::high_resolution_clock::now();
    Matrix m = solve();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time: " << diff.count() << "s" << std::endl;
    return m;
}
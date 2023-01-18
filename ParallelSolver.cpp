#include "ParallelSolver.hpp"

Matrix ParallelSolver::solve() {
    if (!mtx) {
        throw std::invalid_argument("Invalid matrix");
    }

    for (size_t i = 0; i < mtx.matrix.size(); ++i) {
        size_t max = i;
        for (size_t j = i + 1; j < mtx.matrix.size(); ++j) {
            if (std::abs(mtx.matrix[j][i]) > std::abs(mtx.matrix[max][i])) {
                max = j;
            }
        }

        if (mtx.matrix[max][i] == 0) continue;

        mtx.swapRows(i, max);
        mtx.multiplyRow(i, 1 / mtx.matrix[i][i]);

        std::vector<std::thread> threads;
        for (size_t j = 0; j < mtx.matrix.size(); ++j) {
            if (i != j) {
                threads.push_back(std::thread(&Matrix::addRows, &mtx, j, i, -mtx.matrix[j][i]));
            }
        }

        for (size_t j = 0; j < threads.size(); ++j) {
            threads[j].join();
        }
    }
    return mtx;
}
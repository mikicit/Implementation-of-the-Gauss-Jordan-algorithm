#include "ClassicSolver.hpp"

Matrix ClassicSolver::solve(){
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

        for (size_t j = 0; j < mtx.matrix.size(); ++j) {
            if (i != j) {
                mtx.addRows(j, i, -mtx.matrix[j][i]);
            }
        }
    }

    return mtx;
}
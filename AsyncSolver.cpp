#include "AsyncSolver.hpp"

void AsyncSolver::solve_thread(size_t i){
    while(true) {
        Task task;

        // Use lock_guard to automatically unlock the mutex when it leaves the area of visibility.

        {
            std::lock_guard<std::mutex> lock(mutex); // lock mutex
            if (tasks.empty()) return; // if tasks query is empty
            task = tasks.front();
            tasks.pop();
        }

        task();
    }
}

Matrix AsyncSolver::solve(){
    if (!mtx) {
        throw std::invalid_argument("Invalid matrix");
    }

    int i = 0;

    Task task = [this,&task,&i](){
        if (i>=mtx.matrix.size()) return;

        size_t max = i;
        for (size_t j = i + 1; j < mtx.matrix.size(); ++j) {
            if (std::abs(mtx.matrix[j][i]) > std::abs(mtx.matrix[max][i])) {
                max = j;
            }
        }

        if (mtx.matrix[max][i] == 0) return;

        mtx.swapRows(i, max);
        mtx.multiplyRow(i, 1 / mtx.matrix[i][i]);

        for (size_t j = 0; j < mtx.matrix.size(); ++j) {
            if (i != j) {
                tasks.push([this,i,j](){
                    mtx.addRows(j, i, -mtx.matrix[j][i]);
                });
            }
        }

        ++i;
        tasks.push(task);
    };

    tasks.push(task);

    for (size_t i = 0; i < threads.size(); ++i){
        threads[i] = std::thread(&AsyncSolver::solve_thread, this, i);
    }

    for (size_t i = 0; i < threads.size(); ++i){
        threads[i].join();
    }

    return mtx;
}
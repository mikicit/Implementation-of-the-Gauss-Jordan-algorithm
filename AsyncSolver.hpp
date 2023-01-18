#include "Solver.hpp"
#include <functional>
#include <mutex>
#include <queue>

#ifndef GAUSS_ASYNC_SOLVER_H
#define GAUSS_ASYNC_SOLVER_H

typedef std::function<void()> Task;
typedef std::queue<Task> TaskQueue;

// Implementation of the Solver class for the asynchronous algorithm.
class AsyncSolver : public Solver {
    std::vector<std::thread> threads; // vector with threads
    std::mutex mutex; // mutex for task queue for sharing access to tasks
    TaskQueue tasks; // queue of tasks (functions)
    void solve_thread(size_t i); // Executes a task from the task queue until the tasks run out.
public:
    // Standard constructor.
    AsyncSolver(Matrix m, size_t tn) : Solver(m), threads(tn) {}

    // Implementation of the method of the parent class solve.
    Matrix solve() override;
};

#endif
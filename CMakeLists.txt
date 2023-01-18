cmake_minimum_required(VERSION 3.5)
project(gauss)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(core-files
        Matrix.hpp
        Matrix.cpp
        Solver.hpp
        Solver.cpp
        ClassicSolver.hpp
        ClassicSolver.cpp
        ParallelSolver.cpp
        AsyncSolver.hpp
        AsyncSolver.cpp AsyncSolver.cpp)

add_executable(gauss
    main.cpp
    ${core-files}
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(gauss Threads::Threads)

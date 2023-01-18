#include "Matrix.hpp"
#include "Solver.hpp"
#include "ClassicSolver.hpp"
#include "ParallelSolver.hpp"
#include "AsyncSolver.hpp"
#include <iostream>
#include <fstream>

void printHelp(){
    std::cout << "Usage: ./gauss {-h | --help |-f <file> | -c | -r <x> <y>} {-s|-a|-p} {-S|-F}" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h, --help Show this help message and exit" << std::endl;
    std::cout << "  -f <file> Read matrix from file" << std::endl;
    std::cout << "  -r <x> <y> Generate random matrix with size <x> <y>" << std::endl;
    std::cout << "  -c Enter matrx from console" << std::endl;
    std::cout << "  -a Use async solver" << std::endl;
    std::cout << "  -p Use parallel solver" << std::endl;
    std::cout << "  -s Use classic solver" << std::endl;
    std::cout << "  -S Short" << std::endl;
    std::cout << "  -F Full" << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 2 || argv[1] == std::string("-h") || argv[1] == std::string("--help")) {
        printHelp();
        return 0;
    }

    Matrix matrix;
    int p = 0;
    if (argv[1] == std::string("-f")) {
        if (argc < 3){
            printHelp();
            return 0;
        }

        std::ifstream file(argv[2]);
        if (!file.is_open()) {
            std::cout << "Can't open file" << std::endl;
            return 0;
        }

        file >> matrix;
        p = 3;
    }
    else if (argv[1] == std::string("-r")) {
        if (argc < 4) {
            printHelp();
            return 0;
        }

        matrix = Matrix(std::stoi(argv[2]), std::stoi(argv[3]));
        p = 4;
    } else if (argv[1] == std::string("-c")) {
        std::cin >> matrix;
        p = 2;
    } else {
        printHelp();
        return 0;
    }

    // Selecting solver
    int solvern = 0;

    if (argc > p){
        if (argv[p] == std::string("-s")) {
            solvern = 0;
        } else if (argv[p] == std::string("-p")) {
            solvern = 1;
        } else if (argv[p] == std::string("-a")) {
            solvern = 2;
        } else {
            printHelp();
            return 0;
        }

        p++;
    }

    if (argc > p + 1) {
        printHelp();
        return 0;
    }

    if (argc <= p || argv[p] == std::string("-S")) {
        switch(solvern) {
            case 0:
                matrix = ClassicSolver(matrix).solve();
                break;
            case 1:
                matrix = ParallelSolver(matrix).solve();
                break;
            case 2:
                matrix = AsyncSolver(matrix,4).solve();
                break;
        }
    } else if(argv[p] == std::string("-F")){
        // Write out as system of equations
        std::cout << "Given system as as system of equations." << std::endl;
        matrix.print_as_system_of_equations(std::cout);

        switch(solvern) {
            case 0:
                matrix = ClassicSolver(matrix).solve_and_print_time();
                break;
            case 1:
                matrix = ParallelSolver(matrix).solve_and_print_time();
                break;
            case 2:
                matrix = AsyncSolver(matrix,4).solve_and_print_time();
                break;
        }

        // Write out the solved system of equations
        std::cout << "Solved system as as system of equations." << std::endl;
        matrix.print_as_system_of_equations(std::cout);
    } else {
        printHelp();
        return 0;
    }

    matrix.print_solution(std::cout);
}

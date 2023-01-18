#include "Matrix.hpp"

#define EPSILON 0.0001 // Determination of acceptable accuracy.

void Matrix::print(std::ostream &out) const {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            if (std::abs(matrix[i][j]) < EPSILON) {
                out << 0 << " ";
            } else {
                out << matrix[i][j] << " ";
            }
        }
        out << std::endl;
    }
}

void Matrix::print_as_system_of_equations(std::ostream &out) const {
    for (const auto& i : matrix) {
        bool first = true;

        for (size_t j = 0; j < i.size() - 1; ++j) {
            if (std::abs(i[j]) > EPSILON){
                if (i[j] < 0) {
                    first=false;
                    out << " - ";
                } else if (i[j] > 0) {
                    if (first) {
                        first = false;
                    } else {
                        out << " + ";
                    }
                }

                if(std::abs(std::abs(i[j])-1) > EPSILON) {
                    out << std::abs(i[j]) << "*";
                }

                out << "x" << j+1;
            }
        }

        if (!first) {
            out << " = " << i[i.size() - 1] << std::endl;
        }
    }
}

void Matrix::print_solution(std::ostream &out) const {
    Matrix solution = get_solution();

    // If the matrix size is 0, there are no solutions.
    // If 1, then there is only one solution, if more than 1,
    // then there are many solutions (we get a partial solution as 1 vector,
    // and the remaining vectors represent the base).

    if (solution.matrix.size() == 0) {
        out << "No solution" << std::endl;
    } else if (solution.matrix.size() == 1) {
        out << "Solution: " << std::endl;

        out << "( ";
        for (size_t i = 0; i < solution.matrix[0].size(); ++i) {
            if (std::abs(solution.matrix[0][i]) > EPSILON) {
                out << solution.matrix[0][i] << " ";
            } else {
                out << "0 ";
            }
        }
        out << ")" << std::endl;
    } else {
        out << "Infinite solutions: " << std::endl;
        out << "Particular" << std::endl;
        out << "( ";

        for (size_t i = 0; i < solution.matrix[0].size(); ++i) {
            if (std::abs(solution.matrix[0][i]) > EPSILON) {
                out << solution.matrix[0][i] << " ";
            } else {
                out << "0 ";
            }
        }

        out << ")" << std::endl;
        out << "Span" << std::endl;

        for (size_t i = 1; i < solution.matrix.size(); ++i) {
            out<<"( ";

            for (size_t j = 0; j < solution.matrix[i].size(); ++j) {
                if (std::abs(solution.matrix[i][j]) > EPSILON) {
                    out << solution.matrix[i][j] << " ";
                } else {
                    out << "0 ";
                }
            }

            out << ")" << std::endl;
        }
    }
}

// Reads the matrix from the input stream.
void Matrix::read(std::istream &in) {
    std::string line;

    while (std::getline(in, line, '\n')) {
        if (line.empty()) break; // Finish reading by pressing enter twice (empty line).
        std::istringstream iss(line);
        std::vector<long double> row;
        long double x;

        while (iss >> x) {
            row.push_back(x);
        }

        matrix.push_back(row);
    }

    // If the matrix is not square, the remaining rows are filled with zeros.
    while(matrix.size() < matrix[0].size()-1) {
        matrix.emplace_back(matrix[0].size(),0);
    }
}

void Matrix::swapRows(size_t i, size_t j) {
    std::swap(matrix[i], matrix[j]);

    // Outputs the current state of the matrix to indicate the sequence of changes.
//    print(std::cout);
}

void Matrix::multiplyRow(size_t i, long double k) {
    for (long double& j : matrix[i]) {
        j *= k;
    }

    // Outputs the current state of the matrix to indicate the sequence of changes.
//    print(std::cout);
}

void Matrix::addRows(size_t i, size_t j, long double k) {
    for (size_t l = 0; l < matrix[i].size(); ++l) {
        matrix[i][l] += k * matrix[j][l];
    }

    // Outputs the current state of the matrix to indicate the sequence of changes.
//    print(std::cout);
}

bool Matrix::isvalid() const {
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (matrix[i].size() != matrix.size() + 1) {
            return false;
        }
    }
    return true;
}

Matrix Matrix::get_solution() const {
    size_t rank = get_rank();
    size_t augmented_rank = get_augmented_rank();

    if (rank == augmented_rank) {
        std::vector<long double> solution;

        for (size_t i = 0; i < matrix.size(); ++i) {
            solution.push_back(matrix[i][matrix[i].size() - 1]);
        }

        if (rank == matrix.size()) {
            return Matrix({solution});
        } else {
            std::vector<std::vector<long double>> solution_matrix;
            solution_matrix.push_back(solution);

            for (size_t i = 0; i < matrix.size(); ++i) {
                bool is_zero = true;

                for (size_t j = 0; j < matrix[i].size() - 1; ++j) {
                    if (std::abs(matrix[i][i]) > EPSILON) {
                        is_zero = false;
                        break;
                    }
                }

                if (is_zero) {
                    std::vector<long double> row;

                    for (size_t j = 0; j < matrix.size() ; ++j) {
                        if (i == j) {
                            row.push_back(-1);
                        } else {
                            row.push_back(matrix[j][i]);
                        }
                    }

                    solution_matrix.push_back(row);
                }
            }
            return Matrix(solution_matrix);
        }
    } else {
        return Matrix();
    }
}

size_t Matrix::get_augmented_rank() const {
    size_t rank = 0;

    for (size_t i = 0; i < matrix.size(); ++i) {
        if (std::abs(matrix[i][i]) > EPSILON
            || std::abs(matrix[i][matrix.size()]) > EPSILON) {
            ++rank;
        }
    }

    return rank;
}

size_t Matrix::get_rank() const {
    size_t rank = 0;

    for (size_t i = 0; i < matrix.size(); ++i) {
        if (std::abs(matrix[i][i]) > EPSILON) {
            ++rank;
        }
    }

    return rank;
}

void Matrix::generate_random_matrix(size_t r, size_t c){
    for (size_t i = 0; i < r; ++i){
        std::vector<long double> row;

        for (size_t j = 0; j < c; ++j) {
            row.push_back(rand() % 100);
        }

        matrix.push_back(row);
    }
}

Matrix::Matrix() {
    matrix = std::vector<std::vector<long double>>();
}

Matrix::Matrix(const std::vector<std::vector<long double>> &matrix) {
    this->matrix = matrix;
}

Matrix::Matrix(size_t r, size_t c) {
    generate_random_matrix(r, c);
}

Matrix::Matrix(std::istream &in) {
    read(in);
}

Matrix::Matrix(Matrix const &other) {
    matrix = other.matrix;
}

std::ostream &operator<<(std::ostream &out, const Matrix &m) {
    m.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, Matrix &m) {
    m.read(in);
    return in;
}

Matrix::operator bool() const {
    return isvalid();
}
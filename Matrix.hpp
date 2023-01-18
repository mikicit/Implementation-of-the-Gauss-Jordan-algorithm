#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

#ifndef GAUSS_MATRIX_H
#define GAUSS_MATRIX_H

class Matrix {
    // Writes out the extended matrix to the output stream.
    void print(std::ostream &out) const;

    // Reads the matrix from the input stream.
    void read(std::istream &in);

    // Returns the rank of the matrix.
    size_t get_rank() const;

    // Returns the rank of the augmented (expanded) matrix.
    size_t get_augmented_rank() const;

    // Checks if the matrix is valid.
    bool isvalid() const;

    // Generates a random matrix with a certain size for tests.
    void generate_random_matrix(size_t r, size_t c);
public:
    std::vector<std::vector<long double>> matrix;

    // Line swapping operation.
    void swapRows(size_t i, size_t j);

    // Multiplies the row by the coefficient k.
    void multiplyRow(size_t i, long double k);

    // Adds the line with index j multiplied by factor k to the line with index i.
    void addRows(size_t i, size_t j, long double k);

    // Standard constructor.
    Matrix();

    // Create a matrix from a vector of vectors.
    Matrix(const std::vector<std::vector<long double>> &matrix);

    // A constructor for creating a random matrix.
    Matrix(size_t r, size_t c);

    // Copying constructor for tests.
    Matrix(Matrix const &other);

    // A constructor that takes a stream as an argument.
    Matrix(std::istream &in);

    // Outputs the given matrix as a system of linear equations (outputs after setting the matrix).
    void print_as_system_of_equations(std::ostream &out) const;

    // Prints the final solution in formatted form.
    void print_solution(std::ostream &out) const;

    // Returns the solution as a matrix.
    // If the matrix size is 0, there are no solutions.
    // If 1, then there is only one solution, if more than 1,
    // then there are many solutions (we get a partial solution as 1 vector,
    // and the remaining vectors represent the base).
    Matrix get_solution() const;

    // Overloading the bool operator.
    operator bool() const;

    // << operator overload.
    friend std::ostream &operator<<(std::ostream &out, const Matrix &m);

    // >> operator overload.
    friend std::istream &operator>>(std::istream &in, Matrix &m);
};

#endif
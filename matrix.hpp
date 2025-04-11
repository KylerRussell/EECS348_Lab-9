#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template<typename T>
class Matrix {
public:
    // Construct an N×N zero matrix
    Matrix(size_t N)
      : N_(N), data_(N, vector<T>(N, T{})) {}

    // Construct from a 2D vector; throws error if non‑square
    Matrix(const vector<vector<T>>& nums) {
        N_ = nums.size();
        data_ = nums;
        for (auto & row : data_)
            if (row.size() != N_)
                throw runtime_error("Non‑square initializer");
    }

    // Return matrix dimension
    size_t get_size() const { return N_; }

    // Access and modify elements
    T get_value(size_t i, size_t j) const { bounds_check(i,j); return data_[i][j]; }
    void set_value(size_t i, size_t j, T v) { bounds_check(i,j); data_[i][j] = v; }

    // Sum of main diagonal
    T sum_diagonal_major() const {
        T s{}; for (size_t i = 0; i < N_; ++i) s += data_[i][i];
        return s;
    }

    // Sum of minor diagonal
    T sum_diagonal_minor() const {
        T s{}; for (size_t i = 0; i < N_; ++i) s += data_[i][N_ - 1 - i];
        return s;
    }

    // Swap two rows
    void swap_rows(size_t r1, size_t r2) {
        if (r1 >= N_ || r2 >= N_) throw out_of_range("Row index");
        swap(data_[r1], data_[r2]);
    }

    // Swap two columns
    void swap_cols(size_t c1, size_t c2) {
        if (c1 >= N_ || c2 >= N_) throw out_of_range("Col index");
        for (size_t i = 0; i < N_; ++i)
            swap(data_[i][c1], data_[i][c2]);
    }

    // Add two matrices
    Matrix operator+(Matrix const & rhs) const {
        check_same_size(rhs);
        Matrix R(N_);
        for (size_t i = 0; i < N_; ++i)
            for (size_t j = 0; j < N_; ++j)
                R.data_[i][j] = data_[i][j] + rhs.data_[i][j];
        return R;
    }

    // Multiply two matrices
    Matrix operator*(Matrix const & rhs) const {
        check_same_size(rhs);
        Matrix R(N_);
        for (size_t i = 0; i < N_; ++i)
            for (size_t j = 0; j < N_; ++j)
                for (size_t k = 0; k < N_; ++k)
                    R.data_[i][j] += data_[i][k] * rhs.data_[k][j];
        return R;
    }

    // Output matrix to stream
    friend ostream& operator<<(ostream& out, Matrix const& M) {
        for (size_t i = 0; i < M.N_; ++i) {
            for (size_t j = 0; j < M.N_; ++j) {
                out << setw(8) << M.data_[i][j];
            }
            out << "\n";
        }
        return out;
    }

private:
    // Matrix dimension
    size_t N_;
    // Matrix data
    vector<vector<T>> data_;

    // Bounds check
    void bounds_check(size_t i, size_t j) const {
        if (i >= N_ || j >= N_) throw out_of_range("Index");
    } 

    // Check if matrices have same size
    void check_same_size(Matrix const& rhs) const {
        if (rhs.N_ != N_) throw runtime_error("Size mismatch");
    }
};

#endif // __MATRIX_HPP__

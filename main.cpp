#include <fstream>
#include <iostream>
#include <vector>
#include "matrix.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    // Check command‐line arguments
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <matrix_file>\n";
        return 1;
    }

    // Open input file
    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Cannot open file " << argv[1] << "\n";
        return 1;
    }

    // Read header: N and type_flag (ignored after validation)
    size_t N;
    int type_flag;
    fin >> N >> type_flag;
    if (!fin || (type_flag != 0 && type_flag != 1)) {
        cerr << "Invalid header\n";
        return 1;
    }

    // Read two raw matrices of doubles
    auto read_raw = [&](vector<vector<double>>& mat) {
        mat.assign(N, vector<double>(N));
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                fin >> mat[i][j];
    };

    // Read matrices A and B
    vector<vector<double>> rawA, rawB;
    read_raw(rawA);
    read_raw(rawB);

    // Construct Matrix<double> instances
    Matrix<double> A(rawA);
    Matrix<double> B(rawB);

    // Display A and B
    cout << "Matrix A:\n" << A;
    cout << "Matrix B:\n" << B;

    // A + B and A * B
    auto C = A + B;
    cout << "A + B:\n" << C;
    auto D = A * B;
    cout << "A * B:\n" << D;

    // Diagonal sums
    cout << "Sum of A major diagonal: " << A.sum_diagonal_major() << "\n";
    cout << "Sum of A minor diagonal: " << A.sum_diagonal_minor() << "\n";

    // Swap first and last rows
    A.swap_rows(0, N - 1);
    cout << "A after swapping row 0 and last row:\n" << A;

    // Swap first and last columns
    A.swap_cols(0, N - 1);
    cout << "A after swapping col 0 and last col:\n" << A;

    // Update element (1,1)
    A.set_value(1, 1, 999);
    cout << "A after setting A[1][1] = 999:\n" << A;

    return 0;
}

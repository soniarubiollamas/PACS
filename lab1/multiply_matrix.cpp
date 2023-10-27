#include <iostream>
#include <ctime>
#include <cstdlib>

// using namespace std;

// Function to generate random double values within a given range
double randomDouble(double min, double max)
{
    double range = max - min;
    return min + static_cast<double>(rand()) / RAND_MAX * range;
}

// Function to perform matrix multiplication

// double** A: This parameter represents a pointer to a 2D array of double values.
// In C++, a double pointer (double**) is often used to represent a 2D array because it allows you to work with dynamically
// allocated 2D arrays. In this function, A represents the first matrix (matrix A) that you want to multiply.

// double** C: This parameter is also a pointer to a 2D array of double values and is used to store the result of the matrix multiplication.
//  C will contain the product of matrices A and B.

// int N: This parameter specifies the size of the square matrices A, B, and C. It indicates that the matrices are NxN,
// where N is an integer. This is important because matrix multiplication is only defined for square matrices of the same size

void matrixMultiply(double **A, double **B, double **C, int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            C[i][j] = 0.0;
            for (int k = 0; k < N; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
// Function to print a matrix
void printMatrix(double **mat, int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << mat[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    cout << endl;
}
int main()
{
    // Define the size of the matrices (N x N)
    int N = 3; // You can change this value as needed

    // Allocate memory for matrices A, B, and C
    double **A = new double *[N];
    double **B = new double *[N];
    double **C = new double *[N];

    for (int i = 0; i < N; ++i)
    {
        A[i] = new double[N];
        B[i] = new double[N];
        C[i] = new double[N];
    }

    // Specify the range for random values
    double minValue = 0.0;
    double maxValue = 9.0;

    // Initialize matrices A and B with random values
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            A[i][j] = randomDouble(minValue, maxValue);
            B[i][j] = randomDouble(minValue, maxValue);
        }
    }
    // Print matrices A and B
    cout << "Matrix A:" << endl;
    printMatrix(A, N);

    cout << "Matrix B:" << endl;
    printMatrix(B, N);

    // Perform matrix multiplication
    matrixMultiply(A, B, C, N);

    // Print the result (matrix C)
    cout << "Matrix C (Result of Multiplication):" << endl;
    printMatrix(C, N);

    // Deallocate memory for matrices
    for (int i = 0; i < N; ++i)
    {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}

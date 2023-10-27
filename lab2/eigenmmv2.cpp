#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>
#include <sys/time.h>
#include <iomanip>

using namespace Eigen;
using namespace std;

int main(int argc, char *argv[])
{

    struct timeval timestamp;

    gettimeofday(&timestamp, NULL);
    double start_sec = timestamp.tv_sec;
    double start_usec = timestamp.tv_usec;
    

    int N = std::atoi(argv[1]);

    int i, j, k;



    MatrixXd a = MatrixXd::Random(N,N);
    MatrixXd b = MatrixXd::Random(N,N);
    MatrixXd c(N,N);

    gettimeofday(&timestamp, NULL);
    double start_mult_sec = timestamp.tv_sec;
    double start_mult_usec = timestamp.tv_usec;

    c = a * b;

    gettimeofday(&timestamp, NULL);
    double end_sec = timestamp.tv_sec;
    double end_usec = timestamp.tv_usec;
    

    // Calculating time taken by a program in seconds

    if (start_mult_usec < start_usec) {
        start_mult_usec += 1000000; 
        start_mult_sec--;
    }

    double first_part = (start_mult_sec - start_sec) + (start_mult_usec - start_usec) / 1000000.0;

      if (end_usec < start_usec) {
        end_usec += 1000000; 
        end_sec--;
    }

    double matrix_part = (end_sec - start_mult_sec) + (end_usec - start_mult_usec) / 1000000.0;

    cout << "initialice time " << first_part << endl;
    cout << "matrix time " << matrix_part << endl;

    return 0;
}

#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    struct timeval timestamp;

    gettimeofday(&timestamp, NULL);
    double start_sec = timestamp.tv_sec;
    double start_usec = timestamp.tv_usec;
    
    
    int N = std::atoi(argv[1]);

    int i, j, k;

    double **a = new double*[N];
    double **b = new double*[N];
    double **c = new double*[N];

    for(i = 0; i < N; ++i)
    {
	a[i] = new double[N];
	b[i] = new double[N];
	c[i] = new double[N];
    }

    // Storing elements of matrices
    for(i = 0; i < N; ++i)
        for(j = 0; j < N; ++j)
        {
            a[i][j] = ((double)rand()) / RAND_MAX;
	    b[i][j] = ((double)rand()) / RAND_MAX;
        }

    // Initializing elements of matrix c to 0
    for(i = 0; i < N; ++i)
        for(j = 0; j < N; ++j)
            c[i][j] = 0;

    gettimeofday(&timestamp, NULL);
    double start_mult_sec = timestamp.tv_sec;
    double start_mult_usec = timestamp.tv_usec;


    // Multiplying matrix a and b and storing in matrix c
    for(i = 0; i < N; ++i)
        for(j = 0; j < N; ++j)
            for(k = 0; k < N; ++k)
                c[i][j] += a[i][k] * b[k][j];

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

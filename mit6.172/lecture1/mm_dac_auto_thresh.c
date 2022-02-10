/*
 *  Matrix multiplication with Divide and Conquer algorithm
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <cilk/cilk.h>
#include <assert.h>

#define N MATRIX_N
double A[N][N];
double B[N][N];
double C[N][N];

float tdiff(struct timeval *start,
		struct timeval *end){
    return (end->tv_sec - start->tv_sec) +
	    1e-6*(end->tv_usec - start->tv_usec);
}

void mm_base(double *restrict C, int n_C,
	    double *restrict A, int n_A,
	    double *restrict B, int n_B,
	    int n) {
    for (int i = 0; i < n; ++i)
        for (int k = 0; k < n; ++k)
            for (int j = 0; j < n; ++j)
		C[i*n_C+j] = A[i*n_A+k] * B[k*n_B+j];
}

void mm_dac(double *restrict C, int n_C,
	    double *restrict A, int n_A,
	    double *restrict B, int n_B,
	    int n, int thresh) {
    assert((n & (-n)) == n);
    if (n <= thresh) {
	mm_base(C, n_C, A, n_A, B, n_B, n);
    } else {
#define X(M, r, c) (M + (r*(n_ ## M) + c) * (n/2))
        cilk_spawn mm_dac(X(C, 0, 0), n_C, X(A, 0, 0), n_A, X(B, 0, 0), n_B, n/2, thresh);
        cilk_spawn mm_dac(X(C, 0, 1), n_C, X(A, 0, 0), n_A, X(B, 0, 1), n_B, n/2, thresh);
        cilk_spawn mm_dac(X(C, 1, 0), n_C, X(A, 1, 0), n_A, X(B, 0, 0), n_B, n/2, thresh);
        mm_dac(X(C, 1, 1), n_C, X(A, 1, 0), n_A, X(B, 0, 1), n_B, n/2, thresh);
	cilk_sync;

        cilk_spawn mm_dac(X(C, 0, 0), n_C, X(A, 0, 1), n_A, X(B, 1, 0), n_B, n/2, thresh);
        cilk_spawn mm_dac(X(C, 0, 1), n_C, X(A, 0, 1), n_A, X(B, 1, 1), n_B, n/2, thresh);
        cilk_spawn mm_dac(X(C, 1, 0), n_C, X(A, 1, 1), n_A, X(B, 1, 0), n_B, n/2, thresh);
        mm_dac(X(C, 1, 1), n_C, X(A, 1, 1), n_A, X(B, 1, 1), n_B, n/2, thresh);
	cilk_sync;
    }
}

int main(int argc, const char *argv[]) {
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j) {
	    A[i][j] = (double)rand() / (double)RAND_MAX;
	    B[i][j] = (double)rand() / (double)RAND_MAX;
	    C[i][j] = 0;
	}
    }

    struct timeval start, end;

    int threshes[] = {4, 8, 16, 32, 64, 128};

    for(int index = 0; index <  sizeof(threshes)/sizeof(threshes[0]); ++index) {
    	gettimeofday(&start, NULL);
    	int thresh = threshes[index];
    	printf("Compute %dx%d MM in ikj order with tiling thresh=%d\n", N, N, thresh);

	mm_dac(C, N, A, N, B, N, N, thresh);

    	gettimeofday(&end, NULL);
    	printf("Compute %dx%d MM in ikj order with tiling thresh=%d took %0.6f seconds\n", N, N, thresh, tdiff(&start, &end));
    }

    return 0;
}

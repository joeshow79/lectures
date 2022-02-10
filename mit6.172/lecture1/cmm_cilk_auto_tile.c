/*
 *  Matrix multiplication
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <cilk/cilk.h>

#define n MATRIX_N
double A[n][n];
double B[n][n];
double C[n][n];

float tdiff(struct timeval *start,
		struct timeval *end){
    return (end->tv_sec - start->tv_sec) +
	    1e-6*(end->tv_usec - start->tv_usec);
}

int main(int argc, const char *argv[]) {
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j) {
	    A[i][j] = (double)rand() / (double)RAND_MAX;
	    B[i][j] = (double)rand() / (double)RAND_MAX;
	    C[i][j] = 0;
	}
    }

    struct timeval start, end;

    int strides[] = {4, 8, 16, 32, 64, 128};

    for(int index = 0; index <  sizeof(strides)/sizeof(strides[0]); ++index) {
    	gettimeofday(&start, NULL);
    	int stride = strides[index];
    	printf("Compute %dx%d MM in ikj order with tiling stride=%d\n", n, n, stride);
    	cilk_for (int ih = 0; ih < n; ih += stride){
	    cilk_for(int jh = 0; jh < n; jh += stride) {
	    	for(int kh = 0; kh < n; kh += stride) {
        	    for(int il = 0; il < stride; ++il) {
		    	for(int kl = 0; kl < stride; ++kl) {
        	        	for(int jl = 0; jl < stride; ++jl) {
	        	    	    C[ih+il][jh+jl] += A[ih+il][kh+kl] * B[kh+kl][jh+jl];
	    			}
		    	}
	            }
	        }
            }
    	}

    	gettimeofday(&end, NULL);
    	printf("Compute %dx%d MM in ikj order with tiling stride=%d took %0.6f seconds\n", n, n, stride, tdiff(&start, &end));
    }

    return 0;
}

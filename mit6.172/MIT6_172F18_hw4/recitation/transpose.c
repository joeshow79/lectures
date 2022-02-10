#include <stdlib.h>
#include <stdio.h>

#include <cilk/cilk.h>

void transpose(double** A, int n) {
    cilk_for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            double temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

int main(int argc, char** argv) {
   int in = atoi(argv[1]);

   double** arr = malloc(sizeof(double*) * in);

   for (int i = 0; i< in; ++i) {
        arr[i] = malloc(sizeof(double) * in);
   }

   transpose(arr, in);

   return 0;
}

/*root@2546cabee09b:/workspace/src/github/joeshow79/pess/MIT6_172F18_hw4# time CILK_NWORKERS=1 ./transpose 100000*/
/*real    3m39.451s*/
/*user    2m42.956s*/
/*sys     0m56.536s*/
/*root@2546cabee09b:/workspace/src/github/joeshow79/pess/MIT6_172F18_hw4#*/
/*(reverse-i-search)`8': time CILK_NWORKERS=^C./transpose 10000*/
/*root@2546cabee09b:/workspace/src/github/joeshow79/pess/MIT6_172F18_hw4# time CILK_NWORKERS=32 ./transpose 100000*/
/*real    0m58.050s*/
/*user    16m1.588s*/
/*sys     10m56.420s*/


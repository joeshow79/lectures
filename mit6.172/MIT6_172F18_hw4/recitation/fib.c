#include <stdlib.h>
#include <stdio.h>

#include <cilk/cilk.h>

// coarseing to improve the performance
int64_t fib_10(int64_t n) {
  if (n < 2) {
    return n;
  } else {
    return fib_10(n-1) + fib_10(n-2);
    }
}

int64_t fib(int64_t n) {
  if (n < 20) {
    return fib_10(n);
  } else {
    int64_t x, y;
    x = cilk_spawn fib(n-1);
    y = fib(n-2);
    cilk_sync;

    return (x+y);
  }
}

int main(int argc, char** argv) {
   int in = atoi(argv[1]);

   int ret = fib(in);

   printf("Result of %d is %d\n", in, ret);

   return 0;
}

/*root@2546cabee09b:/workspace/src/github/joeshow79/pess/MIT6_172F18_hw4# time CILK_NWORKERS=8 ./fib 45*/
/*Result of 45 is 1134903170*/

/*real    0m1.444s*/
/*user    0m11.508s*/
/*sys     0m0.004s*/
/*root@2546cabee09b:/workspace/src/github/joeshow79/pess/MIT6_172F18_hw4# time CILK_NWORKERS=1 ./fib 45*/
/*Result of 45 is 1134903170*/

/*real    0m8.974s*/
/*user    0m8.976s*/
/*sys     0m0.000s*/

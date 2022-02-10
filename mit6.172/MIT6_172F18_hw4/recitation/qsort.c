/**
 * Parallel quicksort.
 *
 * https://www.uio.no/studier/emner/matnat/ifi/INF3380/v18/undervisningsmateriale/
 * https://www.uio.no/studier/emner/matnat/ifi/INF3380/v18/timeplan/index.html#2-1
 *
 * https://www.uio.no/studier/emner/matnat/ifi/INF3380/v18/undervisningsmateriale/quicksort.c
 * https://www.uio.no/studier/emner/matnat/ifi/INF3380/v10/undervisningsmateriale/inf3380-week12.pdf
 * https://www.uio.no/studier/emner/matnat/ifi/INF3380/v17/undervisningsmateriale/chap9_selected_slides2014.pdf
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <cilk/cilk.h>
/**
 * @brief Swaps two elements (via their pointers).
 *
 * @param a First element.
 * @param b Second element.
 */
void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

/**
 * @brief Create a random list of `n` ints, uniformly sampled between `[0,n)`.
 *
 * @param array Pointer to pointer of array.
 */
void random_array(int **array, int n) {
  int* arr = (int*) malloc(n * sizeof(int));
  if(arr == NULL) {
    fprintf(stderr, "Could not malloc, exiting.\n");
    exit(-1);
  }

  for(int i=0; i<n; i++)
    arr[i] = rand() % n; // choose uniformly between [0,n]
  *array = arr;
}

/**
 * @brief Find the optimal pivot.
 *
 * For large patitions, choosing the median of the first, middle, and last
 * element of the partition allows for the selection of the optimal pivot,
 * according to Sedgewick[1]. This rule counters the case of sorted (or
 * reverse-sorted) input, and gives a better estimate of the optimal pivot (the
 * true median) than selecting any single element, when no information about the
 * ordering of the input is known.
 *
 * @param a Pointer to partition.
 * @param n Length of partition.
 * @returns Optimal pivot index.
 *
 * @ref{1} Sedgewick, Robert Algorithms in C: Fundamentals, Data Structures,
 *          Sorting, Searching, Parts 14.
 */
int optimal_pivot(int *a, int n) {
  /*if ((a[n/2]>a[0] && a[0]>a[n-1]) || (a[n-1]>a[0] && a[0]>a[n/2])) {*/
    /*return 0;*/
  /*}*/
  /*if ((a[0]>a[n/2] && a[n/2]>a[n-1]) || (a[n-1]>a[n/2] && a[n/2]>a[0])) {*/
    /*return n/2;*/
  /*}*/

  // jasonj: use the last element as pivot for convienice
  return n-1;
}

/**
 * Recursive Quicksort.
 *
 * The steps are as follows:
 * - Pick a pivot from the list of sorted numbers.
 * - Put all the numbers lower than that pivot's value into the left subarray,
 *   and all the values higher than the pivot into the right subarray.
 * - Recursively sort each subarray.
 *
 * Some caveats with this approach: what happens if the pivot chosen leads to an
 * inbalance in the left and right subarrays? In order words, how do we enforce
 * better load balancing? One way is to choose a pivot value close to the true
 * median value from the list.
 *
 * @param arr Array to be sorted.
 * @param high Ending index.
 */
void local_qsort(int* arr, int high) {
    printf("local_qsort: %d\n", high);
  if (high <= 1)
    return;

  if (high == 2) {
    if (arr[0] > arr[1])
      swap(&arr[0], &arr[1]);
    return;
  }

  // Find pivot (within each subarray)
  int idx = optimal_pivot(arr, high);
  int pivot = arr[idx];

  int i = partition(arr, high, pivot);
  printf("patition: %d -> %d\n", i, high);

  if (i > 1) {
    local_qsort(&arr[0], i);
  }

  if (i < high - 1) {
    local_qsort(&arr[i+1], high -1 - i);
  }
}

int partition(int* arr, int high, int pivot) {
    int i = -1;
    for (int j = 0; j < high - 1; ++j) {
        if (arr[j] <= pivot) {
            i = i + 1;

            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high - 1]);

    return i+1;
}

int validate(int* arr, int high) {
    if (arr == NULL) {
        fprintf(stderr, "null input, validation failed.\n");
        return -1;
    }

    int max = -1;

    for (int i = 0; i < high; ++i) {
        if ( arr[i] >= max ) {
            max = arr[i];
        } else {
            fprintf(stderr, "array is not monothonic increasing, validation failed at %d element.\n", i);
            return -2;
        }
    }

    fprintf(stderr, "validation passed.\n");
    return 0;
}

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  int *arr;

  random_array(&arr, n);

  local_qsort(arr, n);

  for (int i=0; i<n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  validate(arr, n);

  free(arr);
}

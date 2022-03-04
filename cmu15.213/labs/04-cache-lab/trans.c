/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

void transpose_by_blocking(int M, int N, int A[N][M], int B[M][N], int ROW_BLOCK_SIZE, int COL_BLOCK_SIZE) {
    for (int io = 0; io < N; io += ROW_BLOCK_SIZE) {
        for(int jo =0; jo < M; jo += COL_BLOCK_SIZE) {
            int ii_bound = N > (io + ROW_BLOCK_SIZE) ? (io + ROW_BLOCK_SIZE) : N;
            int ji_bound = M > (jo + COL_BLOCK_SIZE) ? (jo + COL_BLOCK_SIZE) : M;
            for (int i = io; i < ii_bound; i++) {
                for (int j = jo; j < ji_bound; j++) {
                    B[j][i] = A[i][j];
                }
            }
        }
    }
}

void transpose_by_blocking_diagonal(int M, int N, int A[N][M], int B[M][N], int ROW_BLOCK_SIZE, int COL_BLOCK_SIZE) {
    for (int io = 0; io < N; io += ROW_BLOCK_SIZE) {
        for(int jo =0; jo < M; jo += COL_BLOCK_SIZE) {
            int ii_bound = N > (io + ROW_BLOCK_SIZE) ? (io + ROW_BLOCK_SIZE) : N;
            int ji_bound = M > (jo + COL_BLOCK_SIZE) ? (jo + COL_BLOCK_SIZE) : M;

            for (int i = io; i < ii_bound; i++) {
                int diagonal_key = -1;
                int diagonal_value = -1;

                for (int j = jo; j < ji_bound; j++) {
                    if (i == j) {
                        diagonal_key = i;
                        diagonal_value = A[i][j];
                        /*printf("k: %d, v: %d\n", diagonal_key, diagonal_value);*/
                    } else {
                        B[j][i] = A[i][j];
                    }
                }

                if (-1 != diagonal_key) {
                    B[diagonal_key][diagonal_key] = diagonal_value;
                    diagonal_key = -1;
                }
            }
        }
    }
}

void transpose_by_blocking_diagonal_round(int M, int N, int A[N][M], int B[M][N], int ROW_BLOCK_SIZE, int COL_BLOCK_SIZE) {
    int direction_left_to_right_out = 1;
    for (int io = 0; io < N; io += ROW_BLOCK_SIZE) {

        if (direction_left_to_right_out) {
            for(int jo =0; jo < M; jo += COL_BLOCK_SIZE) {
                int ii_bound = N > (io + ROW_BLOCK_SIZE) ? (io + ROW_BLOCK_SIZE) : N;
                int ji_bound = M > (jo + COL_BLOCK_SIZE) ? (jo + COL_BLOCK_SIZE) : M;
                int direction_left_to_right_in = 1;

                for (int i = io; i < ii_bound; i++) {
                    int diagonal_key = -1;
                    int diagonal_value = -1;

                    if (direction_left_to_right_in) {
                        for (int j = jo; j < ji_bound; j++) {
                            if (i == j) {
                                diagonal_key = i;
                                diagonal_value = A[i][j];
                            } else {
                                B[j][i] = A[i][j];
                            }
                        }
                    } else {
                        for (int j = ji_bound - 1; j >= jo; j--) {
                            if (i == j) {
                                diagonal_key = i;
                                diagonal_value = A[i][j];
                            } else {
                                B[j][i] = A[i][j];
                            }
                        }
                    }

                    direction_left_to_right_in = ! direction_left_to_right_in;

                    if (-1 != diagonal_key) {
                        B[diagonal_key][diagonal_key] = diagonal_value;
                        diagonal_key = -1;
                    }
                }
            }
        } else {
            for(int jo = M - 1; jo >= 0 ; jo -= COL_BLOCK_SIZE) {
                int ii_bound = N > (io + ROW_BLOCK_SIZE) ? (io + ROW_BLOCK_SIZE) : N;
                int ji_bound = (jo - COL_BLOCK_SIZE) < 0 ? 0: (jo - COL_BLOCK_SIZE) ;
                int direction_left_to_right_in = 1;

                for (int i = io; i < ii_bound; i++) {
                    int diagonal_key = -1;
                    int diagonal_value = -1;

                    if(direction_left_to_right_in) {
                        for (int j = ji_bound; j <= jo; j++) {
                            if (i == j) {
                                diagonal_key = i;
                                diagonal_value = A[i][j];
                            } else {
                                B[j][i] = A[i][j];
                            }
                        }
                    } else {
                        for (int j = jo; j >= ji_bound; j--) {
                            if (i == j) {
                                diagonal_key = i;
                                diagonal_value = A[i][j];
                            } else {
                                B[j][i] = A[i][j];
                            }
                        }

                    }

                    direction_left_to_right_in = ! direction_left_to_right_in;

                    if (-1 != diagonal_key) {
                        B[diagonal_key][diagonal_key] = diagonal_value;
                        diagonal_key = -1;
                    }
                }
            }

        }

        // testing shows that apply the round style on the outer loop may degrade the performance
        /*direction_left_to_right_out = ! direction_left_to_right_out;*/
    }
}

void transpose_by_blocking_l2_diagonal(int M, int N, int A[N][M], int B[M][N], int L1_ROW_BLOCK_SIZE, int L1_COL_BLOCK_SIZE, int L2_ROW_BLOCK_SIZE, int L2_COL_BLOCK_SIZE) {
    for (int io = 0; io < N; io += L1_ROW_BLOCK_SIZE) {
        for(int jo =0; jo < M; jo += L1_COL_BLOCK_SIZE) {

            int ii1_bound = N > (io + L1_ROW_BLOCK_SIZE) ? (io + L1_ROW_BLOCK_SIZE) : N;
            int ji1_bound = M > (jo + L1_COL_BLOCK_SIZE) ? (jo + L1_COL_BLOCK_SIZE) : M;

                for (int ji1 = jo; ji1 < ji1_bound; ji1 += L2_COL_BLOCK_SIZE) {
            for (int ii1 = io; ii1 < ii1_bound; ii1 += L2_ROW_BLOCK_SIZE) {

                    int ii2_bound = N > (ii1 + L2_ROW_BLOCK_SIZE) ? (ii1 + L2_ROW_BLOCK_SIZE) : N;
                    int ji2_bound = M > (ji1 + L2_COL_BLOCK_SIZE) ? (ji1 + L2_COL_BLOCK_SIZE) : M;

                    for (int i = ii1; i < ii2_bound; i++) {
                        int diagonal_key = -1;
                        int diagonal_value = -1;

                        for (int j = ji1; j < ji2_bound; j++) {
                            if (i == j) {
                                diagonal_key = i;
                                diagonal_value = A[i][j];
                            } else {
                                B[j][i] = A[i][j];
                            }
                        }

                        if (-1 != diagonal_key) {
                            B[diagonal_key][diagonal_key] = diagonal_value;
                            diagonal_key = -1;
                        }
                    }
                }
            }
        }
    }
}

char transpose_block8x8_diagonal_desc[] = "Transpose solution blocking by 8x8 diagonal optimized";
void transpose_block8x8_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 8, 8);
}

char transpose_block16x8_diagonal_desc[] = "Transpose solution blocking by 16x8 diagonal optimized";
void transpose_block16x8_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 16, 8);
}

char transpose_block32x8_diagonal_desc[] = "Transpose solution blocking by 32x8 diagonal optimized";
void transpose_block32x8_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 32, 8);
}

char transpose_block8x8_desc[] = "Transpose solution blocking by 8x8";
void transpose_block8x8(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking(M, N, A, B, 8, 8);
}

char transpose_block2x2_diagonal_desc[] = "Transpose solution blocking by 2x2 diagonal optimzed";
void transpose_block2x2_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 2, 2);
}

char transpose_block2x4_diagonal_desc[] = "Transpose solution blocking by 2x4 diagonal optimzed";
void transpose_block2x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 2, 4);
}

char transpose_block2x8_diagonal_desc[] = "Transpose solution blocking by 2x8 diagonal optimzed";
void transpose_block2x8_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 2, 8);
}

char transpose_block4x4_diagonal_desc[] = "Transpose solution blocking by 4x4 diagonal optimzed";
void transpose_block4x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 4, 4);
}

char transpose_block3x4_diagonal_desc[] = "Transpose solution blocking by 3x4 diagonal optimzed";
void transpose_block3x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 3, 4);
}

char transpose_block5x4_diagonal_desc[] = "Transpose solution blocking by 5x4 diagonal optimzed";
void transpose_block5x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 5, 4);
}

char transpose_block6x4_diagonal_desc[] = "Transpose solution blocking by 6x4 diagonal optimzed";
void transpose_block6x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 6, 4);
}

char transpose_block4x8_diagonal_desc[] = "Transpose solution blocking by 4x8 diagonal optimzed";
void transpose_block4x8_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 4, 8);
}

char transpose_block7x4_diagonal_desc[] = "Transpose solution blocking by 7x4 diagonal optimzed";
void transpose_block7x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 7, 4);
}
char transpose_block8x4_diagonal_desc[] = "Transpose solution blocking by 8x4 diagonal optimzed";
void transpose_block8x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 8, 4);
}
char transpose_block9x4_diagonal_desc[] = "Transpose solution blocking by 9x4 diagonal optimzed";
void transpose_block9x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 9, 4);
}
char transpose_block10x4_diagonal_desc[] = "Transpose solution blocking by 10x4 diagonal optimzed";
void transpose_block10x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 10, 4);
}
char transpose_block11x4_diagonal_desc[] = "Transpose solution blocking by 11x4 diagonal optimzed";
void transpose_block11x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 11, 4);
}
char transpose_block12x4_diagonal_desc[] = "Transpose solution blocking by 12x4 diagonal optimzed";
void transpose_block12x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 12, 4);
}
char transpose_block13x4_diagonal_desc[] = "Transpose solution blocking by 13x4 diagonal optimzed";
void transpose_block13x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 13, 4);
}
char transpose_block14x4_diagonal_desc[] = "Transpose solution blocking by 14x4 diagonal optimzed";
void transpose_block14x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 14, 4);
}
char transpose_block15x4_diagonal_desc[] = "Transpose solution blocking by 15x4 diagonal optimzed";
void transpose_block15x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 15, 4);
}
char transpose_block16x4_diagonal_desc[] = "Transpose solution blocking by 16x4 diagonal optimzed";
void transpose_block16x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 16, 4);
}
char transpose_block32x4_diagonal_desc[] = "Transpose solution blocking by 32x4 diagonal optimzed";
void transpose_block32x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 32, 4);
}

char transpose_block4x4_desc[] = "Transpose solution blocking by 4x4";
void transpose_block4x4(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking(M, N, A, B, 4, 4);
}

char transpose_block2x3_diagonal_desc[] = "Transpose solution blocking by 2x3 diagonal optimzed";
void transpose_block2x3_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 2, 3);
}
char transpose_block4x3_diagonal_desc[] = "Transpose solution blocking by 4x3 diagonal optimzed";
void transpose_block4x3_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 4, 3);
}
char transpose_block8x3_diagonal_desc[] = "Transpose solution blocking by 8x3 diagonal optimzed";
void transpose_block8x3_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 8, 3);
}
char transpose_block16x3_diagonal_desc[] = "Transpose solution blocking by 16x3 diagonal optimzed";
void transpose_block16x3_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 16, 3);
}
char transpose_block32x3_diagonal_desc[] = "Transpose solution blocking by 32x3 diagonal optimzed";
void transpose_block32x3_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 32, 3);
}

char transpose_block2x5_diagonal_desc[] = "Transpose solution blocking by 2x5 diagonal optimzed";
void transpose_block2x5_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 2, 5);
}
char transpose_block4x5_diagonal_desc[] = "Transpose solution blocking by 4x5 diagonal optimzed";
void transpose_block4x5_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 4, 5);
}
char transpose_block8x5_diagonal_desc[] = "Transpose solution blocking by 8x5 diagonal optimzed";
void transpose_block8x5_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 8, 5);
}
char transpose_block16x5_diagonal_desc[] = "Transpose solution blocking by 16x5 diagonal optimzed";
void transpose_block16x5_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 16, 5);
}
char transpose_block32x5_diagonal_desc[] = "Transpose solution blocking by 32x5 diagonal optimzed";
void transpose_block32x5_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 32, 5);
}

char transpose_block2x6_diagonal_desc[] = "Transpose solution blocking by 2x6 diagonal optimzed";
void transpose_block2x6_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 2, 6);
}
char transpose_block4x6_diagonal_desc[] = "Transpose solution blocking by 4x6 diagonal optimzed";
void transpose_block4x6_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 4, 6);
}
char transpose_block8x6_diagonal_desc[] = "Transpose solution blocking by 8x6 diagonal optimzed";
void transpose_block8x6_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 8, 6);
}
char transpose_block16x6_diagonal_desc[] = "Transpose solution blocking by 16x6 diagonal optimzed";
void transpose_block16x6_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 16, 6);
}
char transpose_block32x6_diagonal_desc[] = "Transpose solution blocking by 32x6 diagonal optimzed";
void transpose_block32x6_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 32, 6);
}

char transpose_block16x16_desc[] = "Transpose solution blocking by 16x16";
void transpose_block16x16(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking(M, N, A, B, 16, 16);
}

char transpose_block16x16_diagonal_desc[] = "Transpose solution blocking by 16x16 diagonal optimized";
void transpose_block16x16_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 16, 16);
}

char transpose_block32x16_diagonal_desc[] = "Transpose solution blocking by 32x16 diagonal optimized";
void transpose_block32x16_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 32, 16);
}
char transpose_block16x32_diagonal_desc[] = "Transpose solution blocking by 16x32 diagonal optimized";
void transpose_block16x32_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_diagonal(M, N, A, B, 16, 32);
}

char transpose_block_l2_4x4_diagonal_desc[] = "Transpose solution 2 levels blocking by 4x4 diagonal optimzed";
void transpose_block_l2_4x4_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 2, 8);*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 4, 4);     // miss: 1747*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 4, 8);     // miss: 4635*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 8, 8);     // miss: 4635*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 8, 4);     // miss: 1747*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 16, 4);     // miss: 1747*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 16, 3);     // miss:  2447*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 16, 2);     // miss: 2739*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 32, 16);      miss: 4651*/

    transpose_by_blocking_l2_diagonal(M, N, A, B, 64, 64, 4, 4);    // miss: 1747

    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 8, 4, 4);   // miss: 1747*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 8, 16, 4, 4);   // miss: 1747*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 8, 16, 8, 4);    // miss: 1747*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 8, 32, 4, 4);    // miss: 1747*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 32, 4, 4);    // miss: 1747*/

    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 16, 4, 4);   // miss: 1747*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 16, 4, 2);    miss:  7371*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 16, 8, 2);   // miss: 2739*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 16, 8, 4);   // miss: 1747*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 16, 16, 2);   // miss: 2739*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 16, 4, 8); // miss: 4635*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 16, 2, 8); // miss: 4635*/

    // transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 32, 4, 8);  // miss: 4635
     /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 16, 4, 8);  // miss: 4635*/
    transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 16, 8, 4);   // miss: 1795
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 8, 4, 4);      miss: 1747*/
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 8, 4, 8);     // miss: 4635*/
}

char transpose_block_l2_2x8_diagonal_desc[] = "Transpose solution 2 levels blocking by 2x8 diagonal optimzed";
void transpose_block_l2_2x8_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 2, 8);*/
    transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 16, 2, 8);
}
char transpose_block_l2_4x8_diagonal_desc[] = "Transpose solution 2 levels blocking by 4x8 diagonal optimzed";
void transpose_block_l2_4x8_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 4, 8);*/
    transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 16, 4, 8);
}
char transpose_block_l2_8x8_diagonal_desc[] = "Transpose solution 2 levels blocking by 8x8 diagonal optimzed";
void transpose_block_l2_8x8_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 8, 8);*/
    transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 16, 8, 8);
}
char transpose_block_l2_16x8_diagonal_desc[] = "Transpose solution 2 levels blocking by 16x8 diagonal optimzed";
void transpose_block_l2_16x8_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    /*transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 16, 8);*/
    transpose_by_blocking_l2_diagonal(M, N, A, B, 16, 16, 16, 8);
}
char transpose_block_l2_32x8_diagonal_desc[] = "Transpose solution 2 levels blocking by 32x8 diagonal optimzed";
void transpose_block_l2_32x8_diagonal(int M, int N, int A[N][M], int B[M][N])
{
    transpose_by_blocking_l2_diagonal(M, N, A, B, 32, 32, 32, 8);
}
/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if ( (67 == M ) && (61 == N)) {
        transpose_block32x16_diagonal(M, N, A, B);
        return;
    }

    if ( (64 == M ) && (64 == N)) {
        /*transpose_block4x4_diagonal(M, N, A, B);*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 32, 32);  // miss :4289*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 32, 16);  // miss : 3847*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 32, 8);  // miss : 2963*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 32, 4);  // miss : 1771*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 32, 2);  // miss : 2795*/

        /*transpose_by_blocking_diagonal_round(M, N, A, B, 16, 2);  // miss : 2795*/
        transpose_by_blocking_diagonal_round(M, N, A, B, 16, 4);  // miss : 1771
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 16, 3);  // miss :2359*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 16, 5);  // miss : 2623*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 8, 5);  // miss : 2623*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 16, 8);  // miss : 2963*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 16, 16);  // miss : 3847*/

        /*transpose_by_blocking_diagonal_round(M, N, A, B, 4, 4);  // miss : 2518*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 4, 8);  // miss : 3211*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 8, 8);  // miss : 2963*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 16, 8);   miss : 2963*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 32, 8);  // miss : 2963*/

        /*transpose_by_blocking_diagonal_round(M, N, A, B, 8, 32);  // miss : 4289*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 8, 16);  // miss : 3847*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 8, 8);  // miss : 2963*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 8, 4);  // miss : 1771*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 4, 4);  // miss : 1811*/

        // inner & outer loop with round fasion
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 8, 4);  // miss : 2486*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 4, 4);  // miss :2303*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 16, 4);  // miss :2486*/

        /*transpose_by_blocking_diagonal_round(M, N, A, B, 4, 8);  // miss :3455*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 8, 8);  // miss :3430*/
        /*transpose_by_blocking_diagonal_round(M, N, A, B, 16, 8);  // miss :3430*/
        return;
    }

    transpose_block16x8_diagonal(M, N, A, B);
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /*registerTransFunction(transpose_block_l2_4x4_diagonal, transpose_block_l2_4x4_diagonal_desc);*/

    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /*registerTransFunction(transpose_block4x4, transpose_block4x4_desc);*/
    /*registerTransFunction(transpose_block8x8, transpose_block8x8_desc);*/

    /*registerTransFunction(transpose_block2x2_diagonal, transpose_block2x2_diagonal_desc);*/

    /*registerTransFunction(transpose_block2x3_diagonal, transpose_block2x3_diagonal_desc);*/
    /*registerTransFunction(transpose_block4x3_diagonal, transpose_block4x3_diagonal_desc);*/
    /*registerTransFunction(transpose_block8x3_diagonal, transpose_block8x3_diagonal_desc);*/
    /*registerTransFunction(transpose_block16x3_diagonal, transpose_block16x3_diagonal_desc);*/
    /*registerTransFunction(transpose_block32x3_diagonal, transpose_block32x3_diagonal_desc);*/

    /*registerTransFunction(transpose_block2x4_diagonal, transpose_block2x4_diagonal_desc);*/
    /*registerTransFunction(transpose_block3x4_diagonal, transpose_block3x4_diagonal_desc);*/
    /*registerTransFunction(transpose_block4x4_diagonal, transpose_block4x4_diagonal_desc);*/
    /*[>registerTransFunction(transpose_block5x4_diagonal, transpose_block5x4_diagonal_desc);<]*/
    /*registerTransFunction(transpose_block6x4_diagonal, transpose_block6x4_diagonal_desc);*/
    /*registerTransFunction(transpose_block7x4_diagonal, transpose_block7x4_diagonal_desc);*/
    /*registerTransFunction(transpose_block8x4_diagonal, transpose_block8x4_diagonal_desc);*/
    /*[>registerTransFunction(transpose_block9x4_diagonal, transpose_block9x4_diagonal_desc);<]*/
    /*registerTransFunction(transpose_block10x4_diagonal, transpose_block10x4_diagonal_desc);*/
    /*registerTransFunction(transpose_block11x4_diagonal, transpose_block11x4_diagonal_desc);*/
    /*registerTransFunction(transpose_block12x4_diagonal, transpose_block12x4_diagonal_desc);*/
    /*registerTransFunction(transpose_block13x4_diagonal, transpose_block13x4_diagonal_desc);*/
    /*registerTransFunction(transpose_block14x4_diagonal, transpose_block14x4_diagonal_desc);*/
    /*registerTransFunction(transpose_block15x4_diagonal, transpose_block15x4_diagonal_desc);*/
    /*registerTransFunction(transpose_block16x4_diagonal, transpose_block16x4_diagonal_desc);*/
    /*[>registerTransFunction(transpose_block32x4_diagonal, transpose_block32x4_diagonal_desc);<]*/

    /*registerTransFunction(transpose_block2x5_diagonal, transpose_block2x5_diagonal_desc);*/
    /*registerTransFunction(transpose_block4x5_diagonal, transpose_block4x5_diagonal_desc);*/
    /*registerTransFunction(transpose_block8x5_diagonal, transpose_block8x5_diagonal_desc);*/
    /*registerTransFunction(transpose_block16x5_diagonal, transpose_block16x5_diagonal_desc);*/
    /*registerTransFunction(transpose_block32x5_diagonal, transpose_block32x5_diagonal_desc);*/

    /*registerTransFunction(transpose_block2x6_diagonal, transpose_block2x6_diagonal_desc);*/
    /*registerTransFunction(transpose_block4x6_diagonal, transpose_block4x6_diagonal_desc);*/
    /*registerTransFunction(transpose_block8x6_diagonal, transpose_block8x6_diagonal_desc);*/
    /*registerTransFunction(transpose_block16x6_diagonal, transpose_block16x6_diagonal_desc);*/
    /*registerTransFunction(transpose_block32x6_diagonal, transpose_block32x6_diagonal_desc);*/

    /*registerTransFunction(transpose_block2x8_diagonal, transpose_block2x8_diagonal_desc);*/
    /*registerTransFunction(transpose_block4x8_diagonal, transpose_block4x8_diagonal_desc);*/
    /*registerTransFunction(transpose_block8x8_diagonal, transpose_block8x8_diagonal_desc);*/
    /*registerTransFunction(transpose_block16x8_diagonal, transpose_block16x8_diagonal_desc);*/
    /*[>registerTransFunction(transpose_block32x8_diagonal, transpose_block32x8_diagonal_desc);<]*/

    /*[>registerTransFunction(transpose_block_l2_2x8_diagonal, transpose_block_l2_2x8_diagonal_desc);<]*/
    /*registerTransFunction(transpose_block_l2_4x8_diagonal, transpose_block_l2_4x8_diagonal_desc);*/
    /*registerTransFunction(transpose_block_l2_8x8_diagonal, transpose_block_l2_8x8_diagonal_desc);*/
    /*registerTransFunction(transpose_block_l2_16x8_diagonal, transpose_block_l2_16x8_diagonal_desc);*/
    /*registerTransFunction(transpose_block_l2_32x8_diagonal, transpose_block_l2_32x8_diagonal_desc);*/

    /*registerTransFunction(transpose_block16x16, transpose_block16x16_desc);*/
    /*registerTransFunction(transpose_block16x16_diagonal, transpose_block16x16_diagonal_desc);*/
    /*registerTransFunction(transpose_block32x16_diagonal, transpose_block32x16_diagonal_desc);*/

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}


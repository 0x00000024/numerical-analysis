#include "my_solver.h"

#define index_2d(row, col, dim) row*dim+col

void luDecompositionGaussianElimination() {
    int i, ia, j, n, l[4];
    float a[16], b[4], x[4], s[4];
    a[index_2d(0, 0, 4)] = 2; a[index_2d(0, 1, 4)] = 4; a[index_2d(0, 2, 4)] = 0; a[index_2d(0, 3, 4)] = 1; 
    a[index_2d(1, 0, 4)] = 0; a[index_2d(1, 1, 4)] = 1; a[index_2d(1, 2, 4)] = 5; a[index_2d(1, 3, 4)] = 1; 
    a[index_2d(2, 0, 4)] = 0; a[index_2d(2, 1, 4)] = 1; a[index_2d(2, 2, 4)] = 1; a[index_2d(2, 3, 4)] = 1; 
    a[index_2d(3, 0, 4)] = 0; a[index_2d(3, 1, 4)] = 1; a[index_2d(3, 2, 4)] = 2; a[index_2d(3, 3, 4)] = 3; 

    b[0] = 2; b[1] = 7; b[2] = 8; b[3] = 6;

    n = ia = 4;
    printf("***** Equation *****\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) printf("a[%d][%d] = %f, ", i, j, a[index_2d(j, i, 4)]);
        printf("\n");
    }
    printf("b[0] = %f, b[1] = %f, b[2] = %f, b[3] = %f\n", b[0], b[1], b[2], b[3]);
    gespp_(&n, a, &ia, l, s);
    printf("***** After LU-decomposition *****\n");
    printf("s[0] = %f, s[1] = %f, s[2] = %f, s[3] = %f\n", s[0], s[1], s[2], s[3]);
    printf("l[0] = %d, l[1] = %d, l[2] = %d, l[3] = %d\n", l[0], l[1], l[2], l[3]);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) printf("a[%d][%d] = %f, ", i, j, a[index_2d(j, i, 4)]);
        printf("\n");
    }
    solve_(&n, a, &ia, l, b, x);
    printf("***** Solution *****\n");
    printf("x[0] = %f, x[1] = %f, x[2] = %f, x[3] = %f\n", x[0], x[1], x[2], x[3]);
}

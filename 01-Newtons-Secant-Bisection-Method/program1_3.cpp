#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Bisection method
**********************************************/
void program1_3(FILE *fp) {
  double x0 = 0, x1 = 0, x2 = 0;
  int n;

  printf("Bisection method: \n");

  scanf("%lf %lf", &x0, &x1);

  fprintf(fp, "n              xn1               |f(xn1)|\n");

  for (n = 0;; n++) {
    fprintf(fp, "%d  %20.18e  %12.10e\n", n, x1, fabs(_f(x1)));

    if (fabs(_f(x1)) < DELTA || n >= Nmax || (n != 0 && fabs(x1 - x0) < EPSILON)) {
      break;
    }

    x2 = (x0 + x1) / 2.0;
    if (_f(x0) * _f(x2) < 0) {
      x1 = x2;
    } else {
      x0 = x2;
    }
  }

  printf("%d  %20.18e  %12.10e\n", n, x1, fabs(_f(x1)));
}

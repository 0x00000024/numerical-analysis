#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Newton's method
**********************************************/
void program1_1(FILE *fp) {
  double x0 = 0;
  double x1 = 0;
  int n;

  printf("Newton's method: \n");

  scanf("%lf", &x1);

  fprintf(fp, "n            xn1                 |f(xn1)|\n");

  for (n = 0;; n++) {
    fprintf(fp, "%d  %20.18e  %12.10e\n", n, x1, fabs(_f(x1)));

    if (fabs(_f(x1)) < DELTA || n >= Nmax || (n != 0 && fabs(x0 - x1) < EPSILON)) {
      break;
    }

    x0 = x1;
    x1 = x0 - _f(x0) / _fp(x0);
  }
  printf("%d  %20.18e  %12.10e\n", n, x1, fabs(_f(x1)));
}

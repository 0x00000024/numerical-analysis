#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Secant method
**********************************************/
void program1_2(FILE *fp) {
  double x0 = 0, x1 = 0, x2 = 0;
  int n;

  std::cout << "Secant method: " << std::endl;

  scanf("%lf %lf", &x0, &x1);

  fprintf(fp, "n            xn1                 |f(xn1)|\n");

  for (n = 0;; n++) {
    fprintf(fp, "%d  %20.18e  %12.10e\n", n, x1, fabs(_f(x1)));

    if (fabs(_f(x1)) < DELTA || n >= Nmax || (n != 0 && fabs(x1 - x0) < EPSILON)) {
      break;
    }

    x0 = (_f(x0) * x1 - _f(x1) * x0) / (_f(x0) - _f(x1));
    std::swap(x0, x1);
  }
  printf("%d  %20.18e  %12.10e\n", n, x1, fabs(_f(x1)));
}

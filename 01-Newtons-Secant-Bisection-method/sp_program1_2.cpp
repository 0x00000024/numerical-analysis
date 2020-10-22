#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Secant method
**********************************************/
void sp_program1_2(FILE *fp) {
  float x0 = 0, x1 = 0, x3 = 0;
  int n;

  printf("Float: Secant method: \n");

  scanf("%f %f", &x0, &x1);

  fprintf(fp, "n            xn1                 |f(xn1)|         |xn1-xroot|\n");

  for (n = 0;; n++) {
    fprintf(fp, "%d  %20.18e  %12.10e  %12.10e\n", n, x1, fabs(_sp_f(x1)), fabs(x1 - E));

    if (fabs(_sp_f(x1)) < DELTA || n >= Nmax || (n != 0 && fabs(x1 - x0) < EPSILON)) {
      break;
    }

    x3 = x1;
    x1 = x1 - _sp_f(x1) * (x1 - x0) / (_sp_f(x1) - _sp_f(x0));
    x0 = x3;
  }
  printf("%d  %20.18e  %12.10e  %12.10e\n", n, x1, fabs(_sp_f(x1)), fabs(x1 - E));
}

#include "my_solver.h"

extern void program1_1(FILE *fp); // Newton's method
extern void program1_2(FILE *fp); // Secant method
extern void program1_3(FILE *fp); // Bisection method

extern void sp_program1_1(FILE *fp); // Newton's method
extern void sp_program1_2(FILE *fp); // Secant method

double (*_f)(double);
double (*_fp)(double);

float (*_sp_f)(float);
float (*_sp_fp)(float);

int main() {
  FILE *fp;
  fp = fopen("result.txt", "w");

//  // 1.1 Newton's method and Secant method
//  _f = _f1;
//  _fp = _fp1;
//
//  program1_1(fp);
//  program1_2(fp);

//  _f = _f2;
//  _fp = _fp2;
//
//  program1_1(fp);
//  program1_2(fp);
//
//  // 1.2 Newton's method
//  _f = _f3;
//  _fp = _fp3;
//
//  for (int i = 0; i <= 3; ++i)
//    program1_1(fp);

//  // 1.4
//  _f = _f4;
//  _fp = _fp4;
//
//  program1_1(fp);
//  program1_2(fp);
//
//  _sp_f = _sp_f4;
//  _sp_fp = _sp_fp4;
//
//  sp_program1_1(fp);
//  sp_program1_2(fp);

//  // 1.3 Bisection method
//  _f = _f1;
//  _fp = _fp1;
//
//  program1_3(fp);

//  _f = _f2;
//  _fp = _fp2;
//
//  program1_3(fp);

//  _f = _f3;
//  _fp = _fp3;
//
//  program1_1(fp);
//
//  _f = _f3;
//  _fp = _fp3;
//
//  program1_2(fp);
//
  _f = _f3;
  _fp = _fp3;

  program1_3(fp);

//  // last hw
//  _f = _f5;
//  _fp = _fp5;
//
//  program1_1(fp);

  fclose(fp);
}

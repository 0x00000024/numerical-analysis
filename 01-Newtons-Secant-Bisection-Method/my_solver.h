#ifndef __MY_SOLVER_H__
#define __MY_SOLVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <iostream>

#define DELTA 0.000001
#define Nmax 50
#define EPSILON 0.00001
#define E 2.718281828459

double _f1(double x);
double _fp1(double x);

double _f2(double x);
double _fp2(double x);

double _f3(double x);
double _fp3(double x);

double _f4(double x);
double _fp4(double x);

float _sp_f4(float x);
float _sp_fp4(float x);

double _f5(double x);
double _fp5(double x);

#endif  // __MY_SOLVER_H__

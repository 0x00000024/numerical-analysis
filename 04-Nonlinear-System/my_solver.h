#define _CRT_SECURE_NO_WARNINGS

#ifndef __MY_SOLVER_H__
#define __MY_SOLVER_H__

#define SOLNUMS 3

#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <complex>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>

extern "C"
{
    int gespp_(int*, float*, int*, int*, float*);
    int solve_(int*, float*, int*, int*, float*, float*);
    int rpoly_(double*, int*, double*, double*, long int*);
    int hybrj1_(void fcn(int*, double*, double*, double*, int*, int*), int*, double*, double*, double*, int*, double*, int*, double*, int*);
    int hybrd1_(void fcn(int*, double*, double*, int*), int*, double*, double*, double*, int*, double*, int*);
};


void luDecompositionGaussianElimination();
void findRootsOfRealPolynomial(const std::string& readFilename,
                               const std::string& writeFilename);

void analyticJacobianExample1();
void analyticJacobianExample2();
void approximateJacobianExample1();
void approximateJacobianExample2();
void approximateJacobianExample3();
void analyticJacobianExample3();


void writeResult(std::ofstream& ofs, const double* x, const double* fvec, const int& size);

#endif
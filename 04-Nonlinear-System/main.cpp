#include "my_solver.h"

int main(void)
{
    // 01-LU-Decomposition-Gaussian-Elimination
    luDecompositionGaussianElimination();

    // 02-Find-Roots-Of-Real-Polynomial
    for (int i = 1; i <= 6; ++i) {
        std::stringstream readFileName, writeFileName;
        readFileName << "polynomial_02_" << i << ".txt";
        writeFileName << "roots_02_" << i << ".txt";
        findRootsOfRealPolynomial(readFileName.str(), writeFileName.str());
    }

    // 03-04-05-Solve-Systems-Of-Nonlinear-Equations-Approximate-Jacobian-Example
    approximateJacobianExample1();
    approximateJacobianExample2();
    approximateJacobianExample3();

    // 06-07-08-Solve-Systems-Of-Nonlinear-Equations-Analytic-Jacobian-Example
    analyticJacobianExample1();
    analyticJacobianExample2();
    analyticJacobianExample3();
    return 0;
}

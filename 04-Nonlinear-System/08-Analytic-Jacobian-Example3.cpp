#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

// fcn is the name of the user-supplied subroutine which
//   calculates the functions and the jacobian. fcn must
//   be declared in an external statement in the user
//   calling program, and should be written as follows.
// 
//   subroutine fcn(n,x,fvec,fjac,ldfjac,iflag)
//   integer n,ldfjac,iflag
//   double precision x(n),fvec(n),fjac(ldfjac,n)
//   ----------
//   if iflag = 1 calculate the functions at x and
//   return this vector in fvec. do not alter fjac.
//   if iflag = 2 calculate the jacobian at x and
//   return this matrix in fjac. do not alter fvec.
//   ---------
//   return
//   end
void fcn08(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag) {
    // Original function F(x)
    // Functions
    // 3x1 - cos(x2x3) - 0.5 = 0
    // x1^2 - 81(x2+0.1)^2  + sinx3 + 1.06 = 0
    // e^(-x1x2) + 20x3 + (10Pi - 3)/3 = 0
    if (*iflag == 1) {
        fvec[0] = 3.0 * x[0] - std::cos(x[1] * x[2]) - 0.5;
        fvec[1] = std::pow(x[0], 2) - 81.0 * std::pow(x[1] + 0.1, 2) + std::sin(x[2]) + 1.06;
        fvec[2] = std::exp(-x[0] * x[1]) + 20 * x[2] + (10.0 * M_PI - 3.0) / 3.0;
    }
    // Jacobi matrix J(x)
    else if (*iflag == 2) {
        fjac[0] = 3.0;
        fjac[3] = x[2] * std::sin(x[1] * x[2]);
        fjac[6] = x[1] * std::sin(x[1] * x[2]);

        fjac[1] = 2.0 * x[0];
        fjac[4] = -162.0 * (x[1] + 0.1);
        fjac[7] = std::cos(x[2]);

        fjac[2] = -x[1] * std::exp(-x[0] * x[1]);
        fjac[5] = -x[0] * std::exp(-x[0] * x[1]);
        fjac[8] = 20;
    }
}

void analyticJacobianExample3()
{
    // n is a positive integer input variable set to the number
    //   of functions and variables.
    int n = SOLNUMS;

    // x is an array of length n. on input x must contain
    //   an initial estimate of the solution vector. on output x
    //   contains the final estimate of the solution vector.
    double x[SOLNUMS];

    // fvec is an output array of length n which contains
    //   the functions evaluated at the output x.
    double fvec[SOLNUMS];

    // fjac is an output n by n array which contains the
    //   orthogonal matrix q produced by the qr factorization
    //   of the final approximate jacobian.
    double fjac[MATCOLS * MATROWS];

    // ldfjac is a positive integer input variable not less than n
    //   which specifies the leading dimension of the array fjac.
    int ldfjac = SOLNUMS;

    // tol is a nonnegative input variable. termination occurs
    //   when the algorithm estimates that the relative error
    //   between x and the solution is at most tol.
    double tol = TOLERANCE;

    // info is an integer output variable. if the user has
    //   terminated execution, info is set to the (negative)
    //   value of iflag. see description of fcn. otherwise,
    //   info is set as follows.
    //   info = 1   algorithm estimates that the relative error
    //              between x and the solution is at most tol.
    // 
    //   info = 2   number of calls to fcn with iflag = 1 has
    //              reached 100*(n+1).
    // 
    //   info = 3   tol is too small. no further improvement in
    //              the approximate solution x is possible.
    // 
    //   info = 4   iteration is not making good progress.
    int info;

    // wa is a work array of length lwa.
    double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];

    // lwa is a positive integer input variable not less than
    //   (n*(n+13))/2.
    int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

    std::ofstream ofs;
    ofs.open("roots/roots_08.txt");
    if (!ofs.is_open()) {
        std::cerr << "[Error] cannot open roots_08.txt" << std::endl;
        return;
    }

    x[0] = 0.1; x[1] = 0.1; x[2] = -0.1;

    // https://www.netlib.org/minpack/index.html
    // file	hybrj.f hybrj.f plus dependencies
    // gams	F2
    // for solve systems of nonlinear equations(analytic jacobian)

    // file	hybrj1.f hybrj1.f plus dependencies
    // gams	F2
    // for	easy-to-use driver for (minpack/hybrj)
    hybrj1_(fcn08, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

    writeResult(ofs, x, fvec, SOLNUMS);

    x[0] = 0.5; x[1] = 0.0; x[2] = -0.52359877;

    hybrj1_(fcn08, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

    writeResult(ofs, x, fvec, SOLNUMS);

    ofs.close();
}

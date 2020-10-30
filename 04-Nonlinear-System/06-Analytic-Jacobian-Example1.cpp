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
void fcn06(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag) {
    // Original function F(x)
    // Functions
    // e^(2*x1) - x2 + 4 = 0
    // x2 - x3^2 - 1 = 0
    // x3 - sinx1 = 0
    if (*iflag == 1) {
        fvec[0] = std::exp(2 * x[0]) - x[1] + 4;
        fvec[1] = x[1] - std::pow(x[2], 2) - 1;
        fvec[2] = x[2] - std::sin(x[0]);
    }
    // Jacobi matrix J(x)
    else if (*iflag == 2) {
        fjac[0] = 2.0 * std::exp(2 * x[0]);    fjac[3] = -1.0;         fjac[6] = 0.0;
        fjac[1] = 0.0;                         fjac[4] = 1.0;          fjac[7] = -2.0 * x[2];
        fjac[2] = -std::cos(x[0]);	           fjac[5] = 0.0;          fjac[8] = 1.0;
    }
}

void analyticJacobianExample1()
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
    ofs.open("roots/roots_06.txt");
    if (!ofs.is_open()) {
        std::cerr << "[Error] cannot open roots_06.txt" << std::endl;
        return;
    }

    x[0] = 0.0; x[1] = 0.0; x[2] = 0.0; 

    // https://www.netlib.org/minpack/index.html
    // file	hybrj.f hybrj.f plus dependencies
    // gams	F2
    // for solve systems of nonlinear equations(analytic jacobian)

    // file	hybrj1.f hybrj1.f plus dependencies
    // gams	F2
    // for	easy-to-use driver for (minpack/hybrj)
    hybrj1_(fcn06, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

    writeResult(ofs, x, fvec, SOLNUMS);

    x[0] = 1.55; x[1] = 1.39; x[2] = 1.10; 

    hybrj1_(fcn06, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

    writeResult(ofs, x, fvec, SOLNUMS);

    ofs.close();
}

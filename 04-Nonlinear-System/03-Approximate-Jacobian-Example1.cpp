#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

// fcn is the name of the user-supplied subroutine which
//   calculates the functions. fcn must be declared
//   in an external statement in the user calling
//   program, and should be written as follows.
// 
//   subroutine fcn(n,x,fvec,iflag)
//   integer n,iflag
//   double precision x(n),fvec(n)
//   ----------
//   calculate the functions at x and
//   return this vector in fvec.
//   ---------
//   return
//   end
// 
//   the value of iflag should not be changed by fcn unless
//   the user wants to terminate execution of hybrd1.
//   in this case set iflag to a negative integer.
void fcn03(int* n, double* x, double* fvec, int* iflag) {
    // Functions
    // 10 * x1 - 2 * x2^2 + x2 - 2 * x3 - 5
    // 8 * x2^2 + 4 * x3^2 - 9
    // 8 * x2 * x3 + 4
    fvec[0] = 10.0 * x[0] - 2.0 * std::pow(x[1], 2) + x[1] - 2.0 * x[2] - 5.0;
    fvec[1] = 8.0 * std::pow(x[1], 2) + 4.0 * std::pow(x[2], 2) - 9.0;
    fvec[2] = 8.0 * x[1] * x[2] + 4.0;
}

void approximateJacobianExample1()
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
    double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];

    // lwa is a positive integer input variable not less than
    //   (n*(n+13))/2.
    int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

    std::ofstream ofs;
    ofs.open("roots/roots_03.txt");
    if (!ofs.is_open()) {
        std::cerr << "[Error] cannot open roots_03.txt" << std::endl;
        return;
    }

    x[0] = 1.0; x[1] = -1.0; x[2] = 1.0;

    hybrd1_(fcn03, &n, x, fvec, &tol, &info, wa, &lwa);

    writeResult(ofs, x, fvec, SOLNUMS);


    x[0] = 1.0; x[1] = 1.0; x[2] = -1.0;

    hybrd1_(fcn03, &n, x, fvec, &tol, &info, wa, &lwa);

    writeResult(ofs, x, fvec, SOLNUMS);

    ofs.close();
}

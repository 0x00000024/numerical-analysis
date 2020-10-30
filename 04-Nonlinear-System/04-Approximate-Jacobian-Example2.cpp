#include "my_solver.h"

#define SOLNUMS 2
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
void fcn04(int* n, double* x, double* fvec, int* iflag) {
    // Functions
    // 3x^2 - 2y^2 - 1 = 0
    // x^2 - 2x + y^2 + 2y - 8 = 0
    fvec[0] = 3.0 * std::pow(x[0], 2) - 2.0 * std::pow(x[1], 2) - 1.0;
    fvec[1] = std::pow(x[0], 2) - 2.0 * x[0] + std::pow(x[1], 2) + 2.0 * x[1] - 8.0;
}

void approximateJacobianExample2()
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
    ofs.open("roots/roots_04.txt");
    if (!ofs.is_open()) {
        std::cerr << "[Error] cannot open roots_04.txt" << std::endl;
        return;
    }

    struct result {
        double x0;
        double x1;
        double fvec0;
        double fvec1;
    };

    std::unordered_map<double, result> x0_result;
    double hash = 0;
    for (double i = -4; i <= 4; i += 1.0) {
        for (double j = -5; j <= 5; j += 1.0) {
            x[0] = i;
            x[1] = j;

            // https://www.netlib.org/minpack/index.html
            // file	hybrd.f  hybrd.f plus dependencies
            // gams	F2
            // for	solve systems of nonlinear equations (approximate jacobian)

            // file	hybrd1.f  hybrd1.f plus dependencies
            // gams	F2
            // for	easy-to-use driver for (minpack/hybrd)
            hybrd1_(fcn04, &n, x, fvec, &tol, &info, wa, &lwa);

            hash = std::floor(x[0] * 1000.0) / 1000.0;
            if (!x0_result[hash].x0 || fvec[0] < x0_result[hash].fvec0) {
                x0_result[hash].x0 = x[0];
                x0_result[hash].x1 = x[1];
                x0_result[hash].fvec0 = fvec[0];
                x0_result[hash].fvec1 = fvec[1];
            }
        }
    }

    for (auto& x : x0_result) {
        ofs << "x:" << std::endl;
        ofs << std::fixed << std::setw(18) << std::setprecision(15) <<
            x.second.x0 << " " << std::setw(18) << x.second.x1 << std::endl;
        ofs << "fvec:" << std::endl;
        ofs << std::fixed << std::setw(18) << std::setprecision(15) <<
            x.second.fvec0 << " " << std::setw(18) << x.second.fvec1 << std::endl;
        ofs << std::endl;
    }

    ofs.close();
}

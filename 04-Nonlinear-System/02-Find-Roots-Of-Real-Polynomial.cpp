#include "my_solver.h"

void findRootsOfRealPolynomial(const std::string& readFilename, const std::string& writeFilename) {
    std::ifstream ifs;
    std::ofstream ofs;

    ifs.open("polynomials/" + readFilename);
    if (!ifs.is_open()) {
        std::cerr << "[Error] cannot open " + readFilename << std::endl;
        return;
    }
    ofs.open("roots/" + writeFilename);
    if (!ofs.is_open()) {
        std::cerr << "[Error] cannot open " + writeFilename << std::endl;
        return;
    }

    // FINDS THE ZEROS OF A REAL POLYNOMIAL
    // OP  - DOUBLE PRECISION VECTOR OF COEFFICIENTS IN
    //       ORDER OF DECREASING POWERS.
    double* OP = nullptr;

    // DEGREE   - INTEGER DEGREE OF POLYNOMIAL.
    int DEGREE = 0;

    // ZEROR, ZEROI - OUTPUT DOUBLE PRECISION VECTORS OF
    //                REAL AND IMAGINARY PARTS OF THE
    //                ZEROS.
    double* zeror = nullptr;
    double* zeroi = nullptr;

    // FAIL  - OUTPUT LOGICAL PARAMETER, TRUE ONLY IF
    //         LEADING COEFFICIENT IS ZERO OR IF RPOLY
    //         HAS FOUND FEWER THAN DEGREE ZEROS.
    //         IN THE LATTER CASE DEGREE IS RESET TO
    //         THE NUMBER OF ZEROS FOUND.
    long int fail = 0;

    ifs >> DEGREE;
    OP = new double[DEGREE + 1];
    zeror = new double[DEGREE];
    zeroi = new double[DEGREE];

    for (int i = 0; i < DEGREE + 1; ++i) {
        ifs >> OP[i];
    }

    // https://www.netlib.org/toms/index.html
    // file: 493.gz
    // keywords: polynomial zeros
    // gams: F1a1
    // title: RPOLY
    // for: zeros of a real polynomial
    // alg: Jenkins and Traub
    // by: M.A. Jenkins
    // ref: ACM TOMS 1 (1975) 178-189
    rpoly_(OP, &DEGREE, zeror, zeroi, &fail);

    if (fail) {
        ofs << "Fail: " << fail << std::endl;
        return;
    }

    ofs << "zeror:" << std::endl;
    for (int i = 0; i < DEGREE; ++i) {
        ofs << std::fixed << std::setw(14) << std::setprecision(10)
            << zeror[i] << " ";
    }
    ofs << std::endl;

    ofs << "zeroi:" << std::endl;
    for (int i = 0; i < DEGREE; ++i) {
        ofs << std::fixed << std::setw(14) << std::setprecision(10)
            << zeroi[i] << " ";
    }
    ofs << std::endl;

    ofs << "f(x):" << std::endl;
    for (int i = 0; i < DEGREE; ++i) {
        std::complex<double> root(zeror[i], zeroi[i]);
        std::complex<double> answer(0.0, 0.0);
        for (int j = 0; j < DEGREE; ++j) {
            answer += std::pow(root, DEGREE - j) * OP[j];
        }
        answer += OP[DEGREE];

        ofs << std::fixed << std::setw(14) << std::setprecision(10)
            << std::abs(answer) << " ";
    }

    delete[] OP;
    delete[] zeror;
    delete[] zeroi;

    ifs.close();
    ofs.close();
}

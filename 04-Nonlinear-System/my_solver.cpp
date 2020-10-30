#include "my_solver.h"

void writeResult(std::ofstream& ofs, const double* x, const double* fvec, const int& size) {
    ofs << "x:" << std::endl;
    for (int i = 0; i < size; ++i) {
        ofs << std::fixed << std::setw(19) << std::setprecision(15) << x[i] << " ";
    }
    ofs << std::endl;

    ofs << "fvec:" << std::endl;
    for (int i = 0; i < size; ++i) {
        ofs << std::fixed << std::setw(19) << std::setprecision(15) << fvec[i] << " ";
    }
    ofs << std::endl;
}


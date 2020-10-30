cmake_minimum_required(VERSION 3.17)
project(03-Inverse-Transform-Sampling)

set(CMAKE_CXX_STANDARD 20)

add_executable(03-Inverse-Transform-Sampling main.cpp generatePdf.cpp getPseudorandomNumber.cpp my_solver.h generateHistogram.cpp)

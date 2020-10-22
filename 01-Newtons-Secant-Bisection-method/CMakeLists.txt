cmake_minimum_required(VERSION 3.17)
project(01-Newtons-Secant-Bisection-method)

set(CMAKE_CXX_STANDARD 20)

add_executable(01-Newtons-Secant-Bisection-method
        main.cpp my_solver.h function.cpp program1_1.cpp program1_2.cpp program1_3.cpp
        sp_program1_1.cpp sp_program1_2.cpp sp_function.cpp)

cmake_minimum_required(VERSION 3.1)
project(Numerical_Integration)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(integral interface.cpp NumeracialIntegration.cpp tinyexpr.c)



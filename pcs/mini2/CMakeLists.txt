cmake_minimum_required(VERSION 3.18)
project(mini2)

set(CMAKE_CXX_STANDARD 20)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
add_executable(mini2 main.cpp universe.cpp universe.h cell.cpp cell.h)

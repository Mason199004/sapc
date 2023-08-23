cmake_minimum_required(VERSION 3.0)
project(sapc C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE sources src/*.c)

add_executable(sapc ${sources})

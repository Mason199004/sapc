cmake_minimum_required(VERSION 3.0)
project(sapc C)

set(CMAKE_C_STANDARD 23)

file(GLOB_RECURSE sources src/*.c)

add_executable(sapc ${sources})

cmake_minimum_required(VERSION 3.10)
project(jit)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(DEFAULT_RADIX=10)
add_executable(jit-executor jit-executor.cpp)

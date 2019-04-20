cmake_minimum_required(VERSION 3.10)
project(jit)

set(CMAKE_CXX_STANDARD 14)

add_custom_target(collect ./build.sh to_radix)
add_custom_target(build g++ -std=c++14 -DDEFAULT_RADIX=10 -g jit-executor.cpp -o jit-executor)
add_custom_target(run ./jit-executor 1000)
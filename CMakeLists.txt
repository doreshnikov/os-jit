cmake_minimum_required(VERSION 3.10)
project(jit)

set(CMAKE_CXX_STANDARD 14)

add_custom_target(run ./build.sh to_radix && ./jit-executor 100)
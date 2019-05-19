cmake_minimum_required(VERSION 3.10)

project(jit)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined,address,leak,memory")

add_executable(jit-executor jit-executor.cpp)

set(TEMPLATES logarithm)

add_custom_target(collect ./collect.sh ${TEMPLATES})
add_custom_target(build g++ -std=c++14 -DDEFAULT_VALUE=2 -g jit-executor.cpp -o jit-executor)
add_custom_target(run ./jit-executor 1000)

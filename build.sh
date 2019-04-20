#!/usr/bin/env bash

cd script
./dump.sh parse_int
./dump.sh to_string
./extract.sh parse_int
./extract.sh to_string
cd ..

g++ -std=c++14 -g -DDEFAULT_RADIX=$1 jit-executor.cpp -o jit-executor
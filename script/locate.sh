#!/usr/bin/env bash

echo build...
g++ -std=c++14 -g -c -DDEFAULT_RADIX=10 jit-executor.cpp -o resourses/jit10.o
g++ -std=c++14 -g -c -DDEFAULT_RADIX=16 jit-executor.cpp -o resourses/jit16.o

echo dump...
objdump -d resourses/jit10.o >resourses/jit10.dump
objdump -d resourses/jit16.o >resourses/jit16.dump

echo cleaning...
rm resourses/*.o
diff resourses/jit10.dump resourses/jit16.dump >&2
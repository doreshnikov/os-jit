#!/usr/bin/env bash

g++ -std=c++14 -g -c -DDEFAULT_RADIX=10 jit-executor.cpp -o resourses/jit10.o
g++ -std=c++14 -g -c -DDEFAULT_RADIX=16 jit-executor.cpp -o resourses/jit16.o

objdump -d resourses/jit10.o > resourses/jit10.dump
objdump -d resourses/jit16.o > resourses/jit16.dump

rm resourses/*.o
diff resourses/jit10.dump resourses/jit16.dump
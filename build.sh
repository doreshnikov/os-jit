#!/usr/bin/env bash

cd script
for file in "$@"
do
    echo processing ${file}:
    ./dump.sh ${file}
    ./extract.sh ${file}
done
cd ..

g++ -std=c++14 -g -DDEFAULT_RADIX=16 jit-executor.cpp -o jit-executor
echo [!] target built succesfully
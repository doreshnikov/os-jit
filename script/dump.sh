#!/usr/bin/env bash

target=$1

if [[ ${target} != "" ]]; then
    echo [1] build...
    cp ../templates/${target}.tmp ../templates/${target}.cpp
    g++ -std=c++14 -g -c -DDEFAULT_VALUE=2 ../templates/${target}.cpp -o ../resources/${target}.o
    g++ -std=c++14 -g -c -DDEFAULT_VALUE=16 ../templates/${target}.cpp -o ../resources/cmp.o
    mv ../templates/${target}.cpp ../templates/${target}.hpp

    echo [2] dump...
    objdump -d ../resources/${target}.o >../resources/${target}.dump
    objdump -d ../resources/cmp.o >../resources/cmp.dump
    diff ../resources/${target}.dump ../resources/cmp.dump >>.log

    echo [-] cleaning...
    rm ../resources/*.o
    rm ../resources/cmp.dump
else
    echo invalid target
fi
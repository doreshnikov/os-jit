#!/usr/bin/env bash

target=$1

if [[ ${target} != "" ]]; then
    echo build...
    cp ../templates/${target}.tmp ../templates/${target}.cpp
    g++ -std=c++14 -g -c -DDEFAULT_RADIX=10 ../templates/${target}.cpp -o ../resources/${target}.o
    g++ -std=c++14 -g -c -DDEFAULT_RADIX=16 ../templates/${target}.cpp -o ../resources/cmp.o
    mv ../templates/${target}.cpp ../templates/${target}.hpp

    echo dump...
    objdump -d ../resources/${target}.o >../resources/${target}.dump
    objdump -d ../resources/cmp.o >../resources/cmp.dump
    diff ../resources/${target}.dump ../resources/cmp.dump >>.log

    echo cleaning...
    rm ../resources/*.o
    rm ../resources/cmp.dump
else
    echo invalid target
fi
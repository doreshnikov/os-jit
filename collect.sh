#!/usr/bin/env bash

cd script
>.log

for file in "$@"
do
    echo processing ${file}:
    ./dump.sh ${file} 2
    ./extract.sh ${file}
done
cd ..
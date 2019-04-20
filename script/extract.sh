#!/usr/bin/env bash

parse_int="<_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE>:"
to_string="<_Z9to_stringB5cxx11j>:"

mode=0
nsym=0
i=0

argslines=()
taillines=()

echo reading... >&2
while IFS= read -r line
do
    if [[ ${mode} -eq 1 ]]; then
        args=$(echo "${line}" | sed -r 's/.*:\t([^\t]+).*/\1/')
        args=$(echo "${args}" | sed -r 's/([0-9a-f]{2})/0x\1,/g')
        tail=$(echo "${line}" | sed -r 's/.*:\t[^\t]+\t*(.*)/\1/')

        nsym=$(( $nsym > ${#args} ? $nsym : ${#args} ))

        argslines[${i}]="${args}"
        taillines[${i}]="${tail}"
        i=$(( $i + 1 ))
    fi
    if [[ ${line} == *${parse_int}* ]] || [[ ${line} == *${to_string}* ]]; then
        mode=1
        i=0
        echo "collecting ${line}" >&2
    elif [[ ${line} == *"ret"* ]] && [[ ${mode} -eq 1 ]]; then
        sep=$(printf '%-'${nsym}'s' " ")
        echo collected >&2

        for j in $(seq 0 $(( i - 1 )));
        do
            args="${argslines[${j}]}"
            tail="${taillines[${j}]}"
            comment=$([[ ${#tail} == 0 ]] && (echo "") || (echo "// ${tail}"))
            printf '%s%s\t%s\n' "${args}" "${sep:${#args}}" "${comment}"
        done

        mode=0
        nsym=0
        argslines=()
        taillines=()
        echo
    fi
done
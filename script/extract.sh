#!/usr/bin/env bash

target=$1

parse_int="<_Z9parse_intPKc>"
to_string="<_Z9to_stringj>"

target_line=${!target}

if [[ ${target} != "" ]] && [[ ${target_line} != "" ]]; then
    input=../resources/${target}.dump
    output=../templates/${target}.hpp
    echo output is ${output}

    mode=0
    nsym=0
    i=0

    argslines=()
    taillines=()

    echo reading from ${input}...
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
        if [[ ${line} == *${target_line}* ]]; then
            mode=1
            i=0
            echo collecting ${line}
        elif [[ ${line} == *"ret"* ]] && [[ ${mode} -eq 1 ]]; then
            sep=$(printf '%-'${nsym}'s' " ")
            echo collected

            echo $'\n'$'\n'"// @formatter:off" >>${output}
            echo "unsigned char ${target}_code[] = {" >>${output}
            for j in $(seq 0 $(( i - 1 )));
            do
                args="${argslines[${j}]}"
                tail="${taillines[${j}]}"
                comment=$([[ ${#tail} == 0 ]] && (echo "") || (echo "// ${tail}"))
                printf '\t%s%s\t%s\n' "${args}" "${sep:${#args}}" "${comment}" >>${output}
            done
            echo "};" >>${output}
            echo "// @formatter:on" >>${output}

            mode=0
            nsym=0
            argslines=()
            taillines=()
            echo
        fi
    done <${input}
else
    echo invalid target
fi
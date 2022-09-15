#!/bin/bash

file_in=$1
file_args=$2

if [[ -f $file_args ]]; then
    args=$(cat "$file_args")
fi

if [ -z "$(printenv USE_VALGRIND)" ]; then
    if ! ../../app.exe $args < "$file_in"; then
        exit 0
    else
        exit 1
    fi
else
    if ! valgrind ../../app.exe $args < "$file_in"; then
        exit 0
    else
        exit 1
    fi
fi

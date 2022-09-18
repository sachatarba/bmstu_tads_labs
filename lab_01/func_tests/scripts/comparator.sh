#!/bin/bash

file1=$1
file2=$2

if diff "${file1}" "${file2}" > changes.diff; then
    rm -f changes.diff
    exit 0
else
    rm -f changes.diff
    exit 1
fi

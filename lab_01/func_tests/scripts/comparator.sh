#!/bin/bash

file1=$1
file2=$2

grep -Eo "[-+]?[0-9]+\.?[0-9]*" "$file1" > file1.txt
grep -Eo "[-+]?[0-9]+\.?[0-9]*" "$file2" > file2.txt

if diff file1.txt file2.txt > changes.diff; then
    # echo "o yes"
    rm -f file1.txt file2.txt changes.diff
    exit 0
else
    rm -f file1.txt file2.txt changes.diff
    exit 1
fi

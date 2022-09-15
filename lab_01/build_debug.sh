#!/bin/bash

gcc -c ./src/*.c -Wall -Werror -Wpedantic -Wextra -g

#gcc -c main.c -Wall -Werror -Wpedantic -Wextra -g
gcc -o app.exe *.o -lm

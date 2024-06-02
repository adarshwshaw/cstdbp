#!/bin/bash

mkdir build
set -e
pushd build
clang.exe -std=c11 -Wall -Werror -pedantic -c -D_CRT_SECURE_NO_WARNINGS ../cstdbp_string.c
lib.exe /OUT:cstdbp.lib *.o 
cp ../*.h .
rm *.o 
popd


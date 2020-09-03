#!/bin/bash

rm test/random*
g++ generate.cpp -o generate.o
oj g/i ./generate.o

g++ main.cpp
g++ guchoku.cpp -o guchoku.o

for f in test/*.in; do
    echo $f
    ./a.out < $f > main.out
    ./guchoku.o < $f > guchoku.out
    diff main.out guchoku.out
    echo " "
done
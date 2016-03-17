#!/bin/bash
gcc -std=gnu99  -c removeZnaki.c -o removeZnaki.o
gcc -std=gnu99 -c endswith.c -o endswith.o
gcc -std=gnu99 -c my_strcmp.c -o my_strcmp.o
ar r lib_lab.a removeZnaki.o endswith.o my_strcmp.o
gcc -c main.c -o main.o
gcc main.o lib_lab.a -o wynik.out
./wynik.out
rm *.o
rm lib_lab.a




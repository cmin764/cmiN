#! /bin/bash

lex ex3.l
yacc -d ex3.y
gcc lex.yy.c y.tab.c -ll -ly
./a.out

flex lexan.l
yacc parser.y -vd
gcc -o parser.o y.tab.c
./parser.o ${1}
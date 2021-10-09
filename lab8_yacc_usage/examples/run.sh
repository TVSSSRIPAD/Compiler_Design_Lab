flex example1.l
bison example1.y -vd
gcc -o example.o y.tab.c
./example.o
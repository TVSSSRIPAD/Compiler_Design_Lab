#!/bin/bash
flex lexan${1}.l
bison parser${1}.y -d
gcc -o parser${1}.o parser${1}.tab.c 
./parser${1}.o > output.txt
if [ $1 -eq 1 ] || [ $1 -eq 3 ]
then  
python3 convertToDot.py > ir.dot
dot -Tpng ir.dot > ir.png
xdg-open ir.png
fi
rm *yy.c *.h *tab.c   
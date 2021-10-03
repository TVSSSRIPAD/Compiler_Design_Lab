flex "lexan${1}.l"
gcc lex.yy.c
./a.out > "token${1}.txt"
python3 main.py | tee finalOutput.txt
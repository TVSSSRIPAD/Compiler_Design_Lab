Name : T.V.S.S.Sripad
Roll Number: 18CS01008

Steps to write parser with Bison

1. Bison file:

    In declarations Section, we declare yylex and yyerror functions
    Then we declare tokens and start. The next section is rules section.
    After rules, we have extras section where we include lex.yy.c file for defition of yylex() etc 
    and also finally we define yyerror and main functions.


2. Flex file :-
    We write flex files normally as we do for lexical analysis however, we must 
    include y.tab.h file in declarations section of lex file

Steps to run the files :-

1. flex example.l
2. yacc example.y -d
3. gcc -o example.o y.tab.c
4. ./example.o"

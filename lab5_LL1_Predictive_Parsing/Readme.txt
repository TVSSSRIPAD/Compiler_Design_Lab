Compiler Design Lab
Assignment - 5 - Syntax Analysis/Parsing- (LL(1) predictive parser)

Name:- T.V.S.S.Sripad
Roll Number:-  18CS01008

Instructions to run program:-
1. To run program for 1st grammer run:-
    a) Enter input to be parsed in input1.txt file
    b) ./run.sh 1
2. To run program with 2nd grammar:-
    1) Enter input to be parsed in input2.txt file
    b) ./run.sh 2

Note:-
1. The left-factored grammars for the given 1st grammar, 2nd grammar are stored in grammar1.txt, grammar2.txt files respectively.
2. The input to be parsed is to be given in input1.txt, input2.txt for grammar1, grammar2 respectively.
3. First sets, Follow sets for the given grammar are stored in firstsFollows.py file in the form of a python-dictionary data-structure.
4. lexan1.l, lexan2.l are the files with lex codes for tokenizing the given input    according to grammar1 and grammar2 respectively.
5. token1.txt, token2.txt are intermediate files generated after lexical analysis. These files contain tokens identified from given input.
6. main.py is the main file which contains code for predictive parsing.
7. parseTable.py file has code for generating parseTable. It takes grammar, first set, follow set, terminal symbols as parameters. This file is used by main.py file to generate parseTable before parsing.
8. run.sh file takes grammar number (question number 1 or 2) as input and performs lexical analysis followed by parsing and writes the final output to finalOutput.txt file.
9. String ‘_eps’ has been used to denote ‘Epsilon’ everywhere. 
10. Input format for grammar in grammar1.txt or grammar2.txt  is as follows:
    a. First line consists of set of comma separated non-terminals
    b. Second line consists of set of comma separated terminals
    c. Then production rules follow. The production A -> BCD | E is to be given as:-
        A -> B C D | E (Note that B,C,D are to be separated by space)
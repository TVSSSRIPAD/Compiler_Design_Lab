Compiler Design Lab Assignment-1
    
Assignment: Code for RegularExpression to NFA

Name: T.V.S.S.Sripad 

Instructions to run code (on Linux):
1) renfa.cpp file contains code for RegularExpression to NFA conversion.
2) Run install.sh file to install graphviz (for graph simulation) and to compile renfa.cpp file.
3) Run printnfa.sh file with Regular Expression as command line argument. 
   The final NFA will be saved to graph.png file and will be opened.
4) Along with the RE to NFA conversion, I have also implemented DFA Minimization program
   in dfamin.cpp file.

======== RegularExpression to NFA conversion ========
Sample Example :-
1) For the regular expression ((a+b)b)*c, run the following command:
   ./printnfa.sh '((a+b)b)*c'

Note:-
1) The alphabet used for RE to NFA  conversion is all english characters except `e`.
2) Epsilon is denoted by character `e`
3) Phi is denoted by ~ character

Examples:-
1) Example1 consists of nfa for the regular expression: '((a+b)b)*c'
2) Example2 consists of nfa for the regular expression: 'a+bc'

Working:-
1) renfa.cpp file contains code for converting regular expression into nfa. 
2) renfa.cpp accepts the regular expression as command line argument
3) Output of renfa.cpp (i.e., the generated nfa) is written to output.txt file
4) convertToDot.py file converts this nfa into dot format
5) Finally graphviz command line is used to convert dot file to png


======== DFA Minimization ========

Instructions to run Dfa-Minimization: 
1) g++ dfamin.cpp -o dfamin.o
2) ./dfamin.o 

Note:-
1) The alphabet considered for DFA Minimization consists of {0,1} only.
2) The dfamin.cpp file takes input from dfamin.txt file.
3) The states are to be represented by capital English alphabets starting from A
4) Input is given to dfaas.txt as follows: 
   First line consists of no.of states
   Then n lines follow. Each line has 3 space-seperated characters A B C 
      where B is 0 transition from state A and C is 1 transition from state A.
   The next line consists of start state
   The last line consists of space seperated characters representing final states.

Sample input (to be given in dfamin.txt file):-
4
A C B
B B D
C C C
D D D
A
B D
Here A is start state and B, D are final states

Sample Screenshot:-
The dfamin-example folder has a sample Screenshot for the execution of DFA-Minimization
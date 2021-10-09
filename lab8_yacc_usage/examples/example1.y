%{

    #include <stdio.h>
    #include <stdlib.h>
	extern int yylex();
	void yyerror(char* s); 

%}


%token DING DONG DELL
%start rhyme

%%
rhyme : sound place '\n'
        {printf("string valid\n"); exit(0);};
sound : DING DONG;
place : DELL;
%%

#include "lex.yy.c"
int yywrap(){return 1;}
void yyerror(char *s){
    printf("Error!! %s  \n",s);
}
int main() {
    yyparse();
}
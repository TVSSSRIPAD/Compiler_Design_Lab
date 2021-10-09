%{
    #include <stdio.h>
    #include <stdlib.h> 
    #include <math.h>
    #include "lex.yy.c"
    int yylex();
    void yyerror(char *);
%}

%token PLUS MINUS  MULT  DIV  NUM OPEN_BRACKET CLOSE_BRACKET 
%start start

%left PLUS MINUS 
%left MULT DIV MOD
%left OPEN_BRACKET CLOSE_BRACKET

%%

start : E  { printf("Successfully evaluated the expression as %d \n", $$); return  0 ; }


E   : E  PLUS T   { $$ = $1 + $3; }
    | E  MINUS  T { $$ = $1 - $3; }
    | T  
    ;

T   : T MULT S { $$ = $1 * $3; }
    | T MULT MULT S { $$ = pow($1, $4); }
    | T MOD S {$$ = $1 % $3; }
    | T DIV S { $$ = $1 / $3; }
    | S
    ;

S   : NUM { $$ = $1; }
    | MINUS NUM { $$ = - $2; }
    | OPEN_BRACKET E CLOSE_BRACKET { $$ = $2; }
    ;

%%


void yyerror(char *s){
	printf("%s\nError at Line Number : %d\n",s,yylineno);
	exit(1);
}

int main(){
	yyparse();
	return 0;
}
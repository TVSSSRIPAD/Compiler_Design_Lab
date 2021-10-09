%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    extern int yylval;
    #include "y.tab.h"
%}

%option yylineno

%%

"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MULT; }
"/"     { return DIV; }  
"%"     {return MOD;}
[0-9]+  { yylval = atoi(yytext);  return NUM; }
"("     {return OPEN_BRACKET;}
")"     {return CLOSE_BRACKET;}
[ ]*	{}
\n      { return 0; }

%%

// printf("\n %d \n", yylval);
int yywrap(void) { return 1; }
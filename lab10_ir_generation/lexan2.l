%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h> 
%}
 

%%

"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MULT; }
"/"     { return DIV; }  
"%"     {return MOD;}
[0-9]+  {  yylval.val = atoi(yytext) ;  return NUM; }
"("     {return OPEN_BRACKET;}
")"     {return CLOSE_BRACKET;}
[ ]*	{}
\n      { return 0; }

%%
 
int yywrap(void) { return 1; }
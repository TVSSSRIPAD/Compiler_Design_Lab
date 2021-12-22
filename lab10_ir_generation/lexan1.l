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
[0-9]+  { Node *t = (Node *)malloc(sizeof(Node));
            t->val = atoi(yytext);
            t->isOp = 0;
            t->left = NULL;
            t->right = NULL;
            t->nodenumber = nn++;
            yylval = t ;  return NUM; }
"("     {return OPEN_BRACKET;}
")"     {return CLOSE_BRACKET;}
[ ]*	{}
\n      { return 0; }

%%
 
int yywrap(void) { return 1; }
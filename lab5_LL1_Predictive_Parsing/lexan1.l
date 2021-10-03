%{

#include<stdio.h>    

%}

arthmaticop [+|*]
brackets [(|)]
letter [A-Za-z]
id {letter}+
whitespaces [ \t\n]
%%

{arthmaticop} {
    if (!strcmp(yytext, "+")) {printf("+\n");};
    if (!strcmp(yytext, "*")) {printf("*\n");};
    return 1;
}

{brackets} {
    if (!strcmp(yytext, "(")) {printf("(\n");};
    if (!strcmp(yytext, ")")) {printf(")\n");};
    return 2;
}


{id} {
    printf("id\n");
    return 3;
}

{whitespaces} {}

. {
    printf("ERR\n");
    return 0;
}

%%

int yywrap(void) {return 1;}

int main() {
    
    int token_id;
    yyin = fopen("input1.txt", "r");
    while((token_id = yylex()) != 0) {
        // printf("Token ID = %d lexeme = %s\n",  token_id, yytext);
    }
    
    return 0;
}
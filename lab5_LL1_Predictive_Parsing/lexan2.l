%{

#include<stdio.h>    

%}


arthmaticop [+|\-|*|/]
relop [=|<|>]
semicolon ;
brackets [(|)|{|}]
data_type int|float
condn if|else|and|or|not|then
loops while|do|end
io print|scan
prog prog
digit [0-9]
ic {digit}+
fc ({ic}([.]{ic}))
letter [A-Za-z]
assignment (:=)
id {letter}({letter}|{ic})*
whitespaces [ \t\n]

%%

{arthmaticop} {
    if (!strcmp(yytext, "+")) {printf("+\n");};
    if (!strcmp(yytext, "-")) {printf("-\n");};
    if (!strcmp(yytext, "*")) {printf("*\n");};
    if (!strcmp(yytext, "/")) {printf("/\n");};
    return 1;
}


{relop} {
    if (!strcmp(yytext, "<")) {printf("<\n");};
    if (!strcmp(yytext, "=")) {printf("=\n");};
    if (!strcmp(yytext, ">")) {printf(">\n");};
    return 2;
}

{semicolon} {
    if (!strcmp(yytext, ";")) {printf(";\n");};
    return 3;
}

{brackets} {
    if (!strcmp(yytext, "(")) {printf("(\n");};
    if (!strcmp(yytext, ")")) {printf(")\n");};
    if (!strcmp(yytext, "{")) {printf("{\n");};
    if (!strcmp(yytext, "}")) {printf("}\n");};
    return 4;
}

{data_type} {
    if (!strcmp(yytext, "int")) {printf("int\n");};
    if (!strcmp(yytext, "float")) {printf("float\n");};
    return 5;
}

{condn} {
    if (!strcmp(yytext, "if")) {printf("if\n");};
    if (!strcmp(yytext, "then")) {printf("then\n");};
    if (!strcmp(yytext, "else")) {printf("else\n");};
    if (!strcmp(yytext, "and")) {printf("and\n");};
    if (!strcmp(yytext, "or")) {printf("or\n");};
    if (!strcmp(yytext, "not")) {printf("not\n");};
    return 6;
}

{loops} {
    if (!strcmp(yytext, "while")) {printf("while\n");};
    if (!strcmp(yytext, "do")) {printf("do\n");};
    if (!strcmp(yytext, "end")) {printf("end\n");};
    return 7;
}

{io} {
    if (!strcmp(yytext, "print")) {printf("print\n");};
    if (!strcmp(yytext, "scan")) {printf("scan\n");};
    return 8;
}

{prog} {
    if (!strcmp(yytext, "prog")) {printf("prog\n");};
    return 9;
}

{ic} {
    printf("ic\n");   
    return 10;
}

{fc} {
    printf("fc\n");   
    return 11;
}
{assignment} {
    if (!strcmp(yytext, ":=")) {printf(":=\n");};
    return 12;
}
{id} {
    printf("id\n");
    return 13;
}

{whitespaces} {}

. {
    printf("ERR\n");
}

%%

int yywrap(void) {
    return 1;
}

int main() {
     
    int token_id;
     
    yyin = fopen("input2.txt", "r");
    while((token_id = yylex()) != 0) {
        //  printf("TokenID = %d lexeme = %s\n",  token_id, yytext);
    }
    
    return 0;
}
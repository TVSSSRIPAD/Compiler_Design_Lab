%{ 
    #include<stdio.h>
	#include<string.h>
    #define NUMBER 1
    #define KEYWORD 2
    #define IDENTIFIER 3
    #define RELOP 4
	int iskeyword(char *str);
    int line_number=0;
    int token_no=0;
%} 
digit       [0-9]
digits      ({digit}+)
letter      [a-zA-Z]
alphanum    ({letter}|{digit})
number      ({digits}([.]{digits})?([E][+-]?{digits})?) 
identifier  ({letter}{alphanum}*)
relop       ([<]|[>]|[<][=]|[>][=]|[<][>]|[=])
whitespace  [ \t] 
%%  
{number} 	    {
    token_no++;
    printf("Found %10s", "NUMBER" );
    return NUMBER;
}  
{identifier}	{
    token_no++;
    if(iskeyword(yytext)){
        printf("Found %10s", "KEYWORD");
        return KEYWORD;
    }
    printf("Found %10s", "IDENTIFIER");
    return IDENTIFIER;
}
{relop} 		{
    token_no++;
    printf("Found %10s", "RELOP");
    return RELOP;
}
{whitespace}    {}
\n              {line_number++;}
.               {}
%% 

int yywrap(void){return 1;}  

int main(int argc, char*argv[]) 
{ 
	 
    int token;
    yyin=fopen("i2.txt","r");

    while ((token=yylex())!=0)
        printf(" TokenNo: %3d TokenType : %2d lexem : %10s\n", token_no, token, yytext);

    printf("Completed lexical analysis till line #%2d\n", ++line_number);
    return 0; 
} 
int iskeyword(char *str)
{
	if(!strcmp(str,"if") || !strcmp(str,"else") || !strcmp(str,"then")) return 1;
	else return 0;}
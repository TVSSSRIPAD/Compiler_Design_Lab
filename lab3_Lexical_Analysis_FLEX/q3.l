%{ 
    #include<stdio.h>
	#include<string.h>
	#define NUMBER 1
    #define KEYWORD 2
    #define IDENTIFIER 3
	#define DATATYPE 4
    #define RELOP 5 
	#define ARITHMATIC 6
	#define SEPERATOR 7
	#define LOOPS 8
	#define MAIN 9
	#define IO 10
	int iskeyword(char *str);
    int line_number=0;
    int token_no=0; 
%} 
digit       [0-9]
digits    	({digit}+)
letter      [a-zA-Z]
alphanum    ({letter}|{digit})
number      ({digits}([.]{digits})?([E][+-]?{digits})?) 
identifier  ({letter}{alphanum}*)
relop       ([<]|[>]|[<][=]|[>][=]|[!][=]|[=]|[=][=])
arithmatic 	([+]|[-]|[*]|[/])
seperator	[{|}|(|)|;]	
whitespace  [ \t] 
%% 
{number} {
    token_no++;
    printf("Found %10s", "NUMBER" );
    return NUMBER;
}  

{identifier} {
    token_no++;
    iskeyword(yytext);
    return IDENTIFIER;
}

{relop} {
    token_no++;
    printf("Found %10s", "RELOP");
    return RELOP;
}

{arithmatic} {
	token_no++;	 
	printf("Found %10s", "ARITHMATIC");
	return ARITHMATIC;
}
 
{seperator}	{
	token_no++; 
	printf("Found %10s", "SEPERATOR");
	return SEPERATOR;
}

{whitespace}    {}
\n              {line_number++;}
.               {} 
%% 

int yywrap(void){return 1;}  

int main() 
{ 
	int token;

    yyin = fopen("i3.txt", "r"); 

	while ((token=yylex())!=0){
		printf(" TokenNo: %3d TokenType : %2d lexem : %10s\n", token_no, token, yytext);
	}
	printf("Completed lexical analysis till line #%2d\n", ++line_number);
        
	return 0; 
	
} 


int iskeyword(char *str)
{
	if( !strcmp(str,"if") || !strcmp(str,"else") || !strcmp(str,"then"))
	{
		printf("Found %10s", "KEYWORD");
		return KEYWORD;
	}
	else if(!strcmp(str, "while") || !strcmp(str, "for")){
		printf("Found %10s", "LOOPS");
		return LOOPS;
	}
	else if(!strcmp(str, "INT") || !strcmp(str, "FLOAT") || !strcmp(str, "float") || !strcmp(str, "int"))
	{
		printf("Found %10s", "DATATYPE");
		return DATATYPE;
	}
	else if(!strcmp(str, "main")){
		printf("Found %10s", "MAIN");
		return MAIN;
	}
	else if(!strcmp(str, "read") || !strcmp(str, "print")){
		printf("Found %10s", "I/O");
		return IO;
	} 
	else {
		printf("Found %10s", "IDENTIFIER");
		return IDENTIFIER;
	}
}
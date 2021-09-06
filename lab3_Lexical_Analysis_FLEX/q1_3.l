%{ 
#include<stdio.h> 
#include<string.h> 
%} 
%%
(0|(1(01*0)*1))*	{printf("Accepted\n");}
.*			    	{printf("Rejected\n");}
%%

int yywrap(void){} 

int main() 
{    
    yyin = fopen("i1_3.txt", "r");
    yylex(); 

    return 0; 
}
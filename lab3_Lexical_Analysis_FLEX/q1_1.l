%{ 
#include<stdio.h> 
#include<string.h> 
%} 
%%
1*0(1|01*0)*	{printf("Accepted\n");}
.*				{printf("Rejected\n");}
%%

int yywrap(void){return 1;} 

int main() 
{

    yyin = fopen("i1_1.txt", "r");
    
    yylex(); 
 
    return 0; 
}
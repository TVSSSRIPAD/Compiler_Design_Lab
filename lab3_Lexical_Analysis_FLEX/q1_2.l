%{ 
    #include<stdio.h> 
    #include<string.h> 
%}
%s A B C D 
    
%%

<INITIAL>1 BEGIN A;
<INITIAL>0 BEGIN B;
<INITIAL>[^01\n] BEGIN D;
<INITIAL>\n BEGIN INITIAL; {printf("Rejected\n");}
<A>1 BEGIN INITIAL;
<A>0 BEGIN C;
<A>[^01\n] BEGIN D;
<A>\n BEGIN INITIAL; {printf("Rejected\n");}
<B>1 BEGIN C;
<B>0 BEGIN INITIAL;
<B>[^01\n] BEGIN D;
<B>\n BEGIN INITIAL; {printf("Accepted\n");}  
<C>1 BEGIN B;
<C>0 BEGIN A;
<C>[^01\n] BEGIN D;
<C>\n BEGIN INITIAL; {printf("Rejected\n");}  
<D>[^\n] BEGIN D;
<D>\n BEGIN INITIAL; {printf("Invalid string. Rejected\n");}  
%%

int yywrap(void){return 1;} 
int main() 
{       
    yyin = fopen("i1_2.txt", "r"); 
    yylex(); 
    fclose(yyin);
    return 0; 
}
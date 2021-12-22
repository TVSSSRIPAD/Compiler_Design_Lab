%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    

    int variableCounter = 1;

    typedef struct threeAddressCode {
        char code[500];
        char addr[10];
    } threeAddressCode;

    #include "parser2.tab.h"
    #include "lex.yy.c"
 

    void print3AC(char *);
    void gen(threeAddressCode tac1, threeAddressCode tac2, threeAddressCode* tac, char Op);
    int yylex();
    void yyerror(char *);
%}

%token PLUS MINUS  MULT  DIV  NUM OPEN_BRACKET CLOSE_BRACKET 
%start start

%left PLUS MINUS 
%left MULT DIV MOD
%left OPEN_BRACKET CLOSE_BRACKET

%union {
    threeAddressCode threeaddresscode;
    int val;
};

%type <threeaddresscode> start E T S
%type <val> NUM

%%

start : E { printf("Successfully generated 3AC\n"); print3AC($1.code); return 0; }

E   : E PLUS T { sprintf($$.addr, "t%d", variableCounter++); gen($1,$3,&$$,'+'); }
    | E MINUS T { sprintf($$.addr, "t%d", variableCounter++); gen($1,$3,&$$,'-');  }
    | T { strcpy($$.addr, $1.addr); strcpy($$.code, $1.code); }
    ;

T   : T MULT S { sprintf($$.addr, "t%d", variableCounter++); gen($1,$3,&$$,'*');}
    | T DIV S { sprintf($$.addr, "t%d", variableCounter++); gen($1,$3,&$$,'/'); }
    | T MOD S{sprintf($$.addr, "t%d", variableCounter++);   gen($1,$3,&$$,'%'); }
    | S { strcpy($$.addr, $1.addr); strcpy($$.code, $1.code); }
    ;

S   : NUM { sprintf($$.code, "%s", ""); sprintf($$.addr, "%d", $1); }
    | OPEN_BRACKET E CLOSE_BRACKET { strcpy($$.addr, $2.addr); strcpy($$.code, $2.code); }
    ;
%%
 
void gen(threeAddressCode tac1, threeAddressCode tac2, threeAddressCode *tac, char Op) {
    char code[300], op[4];
    op[0]=' ';op[1] = Op; op[2] = ' '; op[3] = '\0';  
    strcpy(tac->code, tac1.code); 
    strcat(tac->code, tac2.code); 
    strcat(tac->code, tac->addr); 
    strcat(tac->code, " = ");
    strcat(tac->code, tac1.addr);
    strcat(tac->code, op);
    strcat(tac->code, tac2.addr); 
    strcat(tac->code, "\n"); 
}

void print3AC(char *code) {
    printf("%s", code);
}
 

void yyerror(char *s){
	printf("%s\nError at Line Number : %d\n",s,yylineno);
	exit(1);
}


int main() {
	yyparse();
	return 0;
}
 
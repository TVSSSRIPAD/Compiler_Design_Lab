%{
    #include <stdio.h>
    #include <stdlib.h>  
    
    static int nn = 0;
    
    
    typedef struct Node{
        struct Node *left,*right;
        int val;
        int nodenumber;
        int isOp;
    }Node;

    #define YYSTYPE Node*

    #include "parser1.tab.h"

    #include "lex.yy.c"

    // Node *root = NULL;
    int yylex();
    void yyerror(char *);
    Node *addNode(int val, Node *l, Node *r);
    void printAST(Node *root);
    
%}

%token PLUS MINUS  MULT  DIV  NUM OPEN_BRACKET CLOSE_BRACKET 
%start start

%left PLUS MINUS 
%left MULT DIV MOD
%left OPEN_BRACKET CLOSE_BRACKET
 
 
%%

start : E  { printf("Successfully built the AST\n"); 
            printf("Root is :- %d\n", $1->nodenumber); 
            printAST($1); return  0 ; }


E   : E  PLUS T   { $$ = addNode((int)('+'), $1, $3) ;   }
    | E  MINUS  T { $$ = addNode((int)('-'), $1, $3) ;  }
    | T  {$$ = $1; }
    ;

T   : T MULT S { $$ = addNode((int)('*'), $1, $3) ; }
    | T MOD S { $$ = addNode((int)('%'), $1, $3) ; }
    | T DIV S { $$ = addNode((int)('/'), $1, $3) ; }
    | S {$$ = $1; }
    ;

S   : NUM { $$ = $1; }
    | OPEN_BRACKET E CLOSE_BRACKET { $$ = $2; }
    ;

%%

Node *addNode(int val,  Node *l, Node *r){
    Node *t = (Node *)malloc(sizeof(Node));
    t->val = val;
    t->isOp = 1;
    t->left = l;
    t->right = r;
    t->nodenumber = nn++;
    return t ; 
}

void printAST(Node *root) {
 
	if(root!=NULL)
	{	printAST(root->left);
        printf(" Node Number :- %d\n", root->nodenumber);
        if(root->isOp == 0){
            printf(" Node Value is :- %d\n", root->val);
            printf("  Left Child and Right Child are :- -1 -1\n");
        }else{
            printf(" Node Value is :- %c\n", root->val);
            printf(" Left Child and Right Child are :- %d %d\n",root->left->nodenumber, root->right->nodenumber);
        }
        printf("-----------------------------------------------------\n"); 
		printAST(root->right);
	}

}

 

void yyerror(char *s){
	printf("%s\nError at Line Number : %d\n",s,yylineno);
	exit(1);
}

int main(){
	yyparse();
	return 0;
}
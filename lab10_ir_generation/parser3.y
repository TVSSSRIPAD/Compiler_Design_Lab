%{
    #include <stdio.h>
    #include <stdlib.h>  
    
    #define MAXNODES 1000

    static int nn = 0;
    
    
    typedef struct Node{
        struct Node *left,*right;
        int val;
        int nodenumber;
        int isOp;
    }Node;

    typedef struct DAGNode{
        struct Node *address;
        struct Node *left,*right;
        int val;
        int nodenumber;
        int isOp;
    }DAGNode;
 

    #include "parser3.tab.h"

    #include "lex.yy.c"

    DAGNode dag[MAXNODES];

    // Node *root = NULL;
    int yylex();
    void yyerror(char *);
    Node *addNode(int val, int isOp, Node *l, Node *r);
    Node *checkIfExists(int val, Node *l, Node *r);
    DAGNode addDAGNode(Node *node);

    void printDAG(Node *root);
    
%}

%token PLUS MINUS  MULT  DIV  NUM OPEN_BRACKET CLOSE_BRACKET 
%start start

%left PLUS MINUS 
%left MULT DIV MOD
%left OPEN_BRACKET CLOSE_BRACKET

%union {
    Node *node;
    int val;
}; 

%type <node> start E T S
%type <val> NUM

%%

start : E  { printf("Successfully built the DAG\n"); 
            printf("Root is :- %d\n", $1->nodenumber);
            printDAG($1); return  0 ; 
            }


E   : E  PLUS T   { $$ = addNode((int)('+'), 1, $1, $3) ;   }
    | E  MINUS  T { $$ = addNode((int)('-'), 1, $1, $3) ;  }
    | T  {$$ = $1; }
    ;

T   : T MULT S { $$ = addNode((int)('*'), 1, $1, $3) ; }
    | T MOD S { $$ = addNode((int)('%'), 1, $1, $3) ; }
    | T DIV S { $$ = addNode((int)('/'), 1, $1, $3) ; }
    | S {$$ = $1; }
    ;

S   : NUM { $$ = addNode($1,0,NULL,NULL); }
    | OPEN_BRACKET E CLOSE_BRACKET { $$ = $2; }
    ;

%%

Node *addNode(int val, int isOp, Node *l, Node *r){
    Node *check = checkIfExists(val, l, r);
    if(check == NULL){

        // printf("not present\n");

        Node *t = (Node *)malloc(sizeof(Node));
        t->val = val;
        t->isOp = isOp;
        t->left = l;
        t->right = r;
        t->nodenumber = nn++;

        dag[nn-1] = addDAGNode(t);

        return t ; 
    }
    else return check;
    
}

DAGNode addDAGNode(Node *node){
    DAGNode *t = (DAGNode *)malloc(sizeof(DAGNode));
    t->address = node;
    t->left = node->left;
    t->right = node->right;
    t->val = node->val;
    t->isOp = node->isOp;
    t->nodenumber = node->nodenumber;
    return *t;
}

Node *checkIfExists(int val, Node *l, Node *r){
    int i;
    for(i=0; i < nn; i++){
        if((dag[i].val == val) && (dag[i].left == l) && ((dag[i].right == r))){
            return dag[i].address;
        }
    }
    return NULL;
}

void printDAG(Node *root) {
 
	int i;
    for(i=0; i < nn; i++){
        printf(" Node Number :- %d\n", dag[i].nodenumber);
        if(dag[i].isOp == 0){
            printf(" Node Value is :- %d\n", dag[i].val);
            printf("  Left Child and Right Child are :- -1 -1\n");
        }else{
            printf(" Node Value is :- %c\n", dag[i].val);
            printf(" Left Child and Right Child are :- %d %d\n",dag[i].left->nodenumber, dag[i].right->nodenumber);
        }
        printf("-----------------------------------------------------\n"); 
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
%{
#include<stdio.h>
void yyerror(const char *str);
int yylex();
int valid=0;
%}

%token IF ELSE RELOP ALPHA NUMBER INDEC

%%

input: if_stmt { if(valid) printf("Valid Syntax\n"); else printf("Invalid Syntax\n"); }
     ;

if_stmt: IF '(' condition ')' stmt_block
       | IF '(' condition ')' stmt_block ELSE stmt_block
       | IF '(' condition ')' stmt_block ELSE if_stmt  // nested if
       { valid=1; }
       ;

stmt_block: '{' '}' ;

condition: ALPHA RELOP ALPHA
         | ALPHA RELOP NUMBER
         ;

%%

int main() {
    printf("Enter nested if statement:\n");
    yyparse();
    return 0;
}

void yyerror(const char *str) {
    printf("An error occurred\n");
}
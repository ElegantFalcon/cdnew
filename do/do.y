%{
#include<stdio.h>
void yyerror(const char *str);
int yylex();
int valid =0;
%}

%token DO WHILE RELOP ALPHA NUMBER INDEC

%%

input : DO stmt_block WHILE '(' condition ')' ';' {printf("Valid Syntax\n"); valid =1;}
        ;

stmt_block : '{' '}' ;

condition: ALPHA RELOP ALPHA
         | ALPHA RELOP NUMBER
         ;
%%

int main(){
    printf("Enter do while loop \n");
    yyparse();
    if(valid==0) printf("Invalid syntax \n");
    return 0;   
}
void yyerror(const char *str){
    printf("an error occurred\n");
}


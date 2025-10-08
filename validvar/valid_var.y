%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
int yyerror(const char*);
%}

%token IDENTIFIER INVALID


%%
input:
    IDENTIFIER  {printf("Valid variable \n");}
    | INVALID    {printf("Invalid variable \n");}
    ;
%%

int yyerror(const char *s){
    printf("Invalid variable name");
    return 1;
}

int main(){
    printf("enter a variable name : ");
    yyparse();
    return 0;
}
%{
#include <stdio.h>
%}

%%
.*Rosh.*  { printf("Invalidddd \n");return 0; }
.*rosh.*  { printf("Invalidddd \n");return 0; }
.* { printf("Validddd \n");return 0; }
%%


int main(void){
    yylex();
    return 0;
}

int yywrap(void) {
    return 1;
}
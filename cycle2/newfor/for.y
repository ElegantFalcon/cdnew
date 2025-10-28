%{
 #include <stdio.h>
 void yyerror(const char *str);
 int yylex();
 int valid =0;
%}

%token FOR RELOP ALPHA NUMBER INDEC

%%
input: FOR '(' initialisation ';' condition ';' updation ')' {printf("Valid Syntax \n"); valid=1;}
            ;

initialisation: ALPHA '=' ALPHA
                | ALPHA '=' NUMBER
                ;

condition: ALPHA RELOP ALPHA
          | ALPHA RELOP NUMBER
          ;


updation: ALPHA INDEC
       ;
 
%%


int main(){
    printf("Enter for loop syntax : ");
    yyparse();
    if(valid==0){
        printf("Invalid syntax\n");
    }
    return 0;
}

void yyerror(const char *str)
  {
    printf("An error occured\n");
}
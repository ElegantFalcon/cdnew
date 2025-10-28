%{
#include "y.tab.h"
%}
   
%%
"for"               { return FOR; }
"++"|"--"              { return INDEC; }
"="                 { return yytext[0]; }
"=="|"<"|">"|"<="|">=" { return RELOP; }
[0-9]+              { return NUMBER;}
[a-zA-Z_][a-zA-Z0-9_]*  { return ALPHA; }
[ \t\n]+            { }
.                   { return yytext[0]; } //for (),{},;
%%


int yywrap(void) {
      return 1;
 }
                
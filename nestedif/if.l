%{
#include "if.tab.h"
%}
%%
"if"            { return IF; }
"else"          { return ELSE; }
"++"|"--"       { return INDEC; }
"="             { return yytext[0]; }
"=="|"<"|">"|"<="|">=" { return RELOP; }
[0-9]+          { return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { return ALPHA; }
[ \t\n]+        { }
.               { return yytext[0]; }
%%
int yywrap(void) { return 1; }
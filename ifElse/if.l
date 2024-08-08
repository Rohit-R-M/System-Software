%{
#include "if.tab.h"
%}
%%
"if" return IF;
"else" return EL;
"(" return OP;
")" return CP;
";" return SEMI;
"{" return OF;
"}" return CF;
[<>=! ]*[= ]? return ROP;
"||" return OR;
"&&" return AND;
[ ]*(statements|statement)  return STA;
[\n\t] ;
[a-zA-Z0-9 ]+ return ID;
%%
int yywrap()
{
    return 1;
}

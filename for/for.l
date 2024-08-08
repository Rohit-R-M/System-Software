%{
#include "for.tab.h"
%}
%%
"for" return FOR;
"(" return OP;
")" return CP;
";" return SEMI;
"{" return OF;
"}" return CF;
"=" return EQL;
"<" return LT;
">" return GT;
"++" return INC;
"--" return DEC;
"statements"  return STA;
[\n\t] ;
[a-zA-Z0-9 ]+ return ID;
%%
int yywrap()
{
    return 1;
}


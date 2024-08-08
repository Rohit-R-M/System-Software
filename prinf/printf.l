%{
#include "printf.tab.h"
%}
%%
"printf"  return P;
\"[a-zA-Z0-9 \=\:\%d\%c\%s\%f\\n]*\" return B;
\,[a-zA-z0-9]+ return BP;
";" return S;
"(" return OP;
")" return CP;
"\t" return SP;
[\n] return 0;
%%
int yywrap()
{
return 1;
}

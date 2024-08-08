%{
#include "scanf.tab.h"
%}

%%

"scanf"    { return S; }
";"        { return SE; }
"("        { return OP; }
")"        { return CP; }
\"[\%d\%c\%f\%s ]+\"  { return MB; }
\,[a-zA-Z]+  { return NB; }
\,\&[a-zA-Z0-9]+  { return AB; }
"&"         { return AMP; }
[\n]       { return 0; }

%%

int yywrap()
{
    return 1;
}

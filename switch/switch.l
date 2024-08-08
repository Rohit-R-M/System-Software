%{
#include "switch.tab.h"
%}

%%
"switch"	return SW;
"("		return OP;
")"		return CP;
":"     return CL;
";"     return SEMI;
"{"     return OF;
"}"     return CF;
"break"	return BR;
"case"	return CASE;
[ ]*(statement|statements)*	return STAT;
[ ]*[a-zA-Z1-9][a-zA-Z]*	return ID;

[\t\n]	;
.		;
%%

int yywrap()
{
return 1;
}

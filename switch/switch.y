%{
#include <stdio.h>
int yylex();
int yyerror();
int flag = 0;
%}

%token SW OP CP CL SEMI OF CF BR STAT ID CASE 
%start E

%%

E : INPUT	{ flag=1; }
  ;
INPUT : SW OP ID CP OF cases CF 
	  | SW OP ID CP OF CF
	  ;
cases : CASE ID CL STAT SEMI BR SEMI cases
	  | CASE ID CL STAT SEMI BR SEMI
	  ;
%%

int main()
{
printf("Enter switch statement\n");
yyparse();
if(flag==1)
	printf("done bro\n");
return 0;
}

int yyerror()
{
printf("Try agian!");
return 1;
}

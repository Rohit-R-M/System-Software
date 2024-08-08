%{
#include<stdio.h>
int yylex();
int yyerror();
int flag=0;
%}
%token P B S OP CP SP BP
%start E
%%
E:P OP VAR CP S    {flag=1;}
 |P OP CP S
 ;
VAR:B 
   |B BP
   ;
%%
int main()
{
printf("The the printf statement:\n");
yyparse();
if(flag==1)
printf("Valid expression\n");
}
int yyerror()
{
printf("Not valid expression\n");
return 0;
}

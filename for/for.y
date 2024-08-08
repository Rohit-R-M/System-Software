%{
#include <stdio.h>
int yyerror();
int yylex();
int flag = 0;
%}
%token FOR OP CP SEMI OF CF ROP STA ID EQL LT GT INC DEC
%start E
%left '+' '-'
%left '='
%%
E:INPUT    {flag=1;}
 ;
INPUT:FOR OP cond CP OF STA SEMI CF   
 |FOR OP cond CP STA SEMI
 ;
cond:ID EQL ID SEMI ID LT ID SEMI ID INC
    |ID EQL ID SEMI ID GT ID SEMI ID INC
|ID EQL ID SEMI ID ROP LT EQL SEMI ID DEC
|ID EQL ID SEMI ID ROP GT EQL SEMI ID DEC
    ;
%%
int main()
{
    printf("Enter the for statement:\n");
    yyparse();
    if (flag == 1)
        printf("valid statement\n");
    return 0;
}
int yyerror()
{
    printf("Invalid Statement\n");
    return 1;
}




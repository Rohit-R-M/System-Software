%{
#include <stdio.h>
int yyerror();
int yylex();
int flag = 0;
%}
%token IF EL OP CP SEMI OF CF ROP OR AND STA ID
%start E
%%
E: INPUT { flag = 1; }
;
INPUT: IF OP cond CP OF stat CF EL OF stat CF
     | IF OP cond CP OF stat CF
     ;
cond: ID ROP ID OR cond
    | ID ROP ID AND cond
    | ID ROP ID
    ;
stat: STA SEMI
    | STA SEMI stat
    ;
%%
int main()
{
    printf("Enter the if statement:\n");
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

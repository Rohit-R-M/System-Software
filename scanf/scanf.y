%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
int yyerror();
int flag = 0;
%}

%token S OP CP MB NB AB SE AMP 
%start E

%%

E: S OP MB ARGS CP SE  { flag = 1; }
  ;

ARGS: AB
     | NB
     | AB NB ARGS
     | AB NB
     ;
%%

int main() 
{
    printf("Enter the scanf statement:\n");
    yyparse();
    if (flag == 1) 
    {
        printf("Valid statement\n");
    }
    return 0;
}

int yyerror() 
{
    printf("Invalid statement\n");
    return 0;
}

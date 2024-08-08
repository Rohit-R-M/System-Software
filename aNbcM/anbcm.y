%{
#include <stdio.h>
int ca = 0, cc = 0;
int yylex(void);
void yyerror();
%}

%token A B C

%%
string: a B c {};
a: A a { ca++; }
 | A { ca++; }
 ;
c: C c { cc++; }
 | C { cc++; }
 ;
%%

int main()
{
    printf("Enter the input :\n");
    yyparse();
    if (ca >= 3 && cc >= 2 && cc <= 3)
        printf("Valid\n");
    else
        printf("Invalid\n");
    return 0;
}

void yyerror()
{
    printf("Invalid\n");
}

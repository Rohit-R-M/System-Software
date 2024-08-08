%{
    #include <stdio.h>
    int  ca=0,cc=0;
    int yylex(void);
    void yyerror();
%}
%token A B c
string a B c{
;}

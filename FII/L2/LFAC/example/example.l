%{
#include <stdio.h>

int yylineno;
%}

%%
(((ab)(abab)*)(([c-z][c-z])+))/[ \n] {fprintf(yyout, "%2d\t\"%s\"\n", yylineno, yytext);}
.|\n {}
%%

int main(int argc, char **argv)
{
    FILE *g;
    if (argc > 0)
     yyin = fopen(argv[1], "r");

    if (!(g = fopen("out.txt","w")))
      fprintf(stderr, "eroare creare fisier!");
    else
      yyout = g;

    yylex();
    fclose(yyin);
    fclose(yyout);
}

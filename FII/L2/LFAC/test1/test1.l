%{
#include <stdio.h>
%}

ndigits [1-9]
digits [0-9]
nr_end [024568]
%%
\{({ndigits}({digits}{2,}){nr_end}|{ndigits}?{nr_end})/\} {fprintf(yyout, "%s\n", yytext+1);}
^([xyt]((abc){3})+)/[ \n] {fprintf(stdout, "%s\n", yytext);}
.|\n {}
%%

int main(int argc, char **argv)
{
    // Cosmin Poieana X (III A6) - nr. 2
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

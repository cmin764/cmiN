%{
#include <stdio.h>
#include "y.tab.h"
%}
%%
[0-9]+ {yylval=atoi(yytext); return SMB;}
[ \t] ;
\n {return 0;}
. {return yytext[0];}


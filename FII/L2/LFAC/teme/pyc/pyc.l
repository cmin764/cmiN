%{
#include <stdio.h>
#include "y.tab.h"
%}

%%

"const" {return CONST;}
"int"|"float"|"str" {return TYPE;}
"func" {return FUNC;}
"endfunc" {return ENDFUNC;}
"return" {return RETURN;}

\$[_a-zA-Z][_a-zA-Z0-9]* {return ID;}
"=" {return ASSIGN;}

[0-9]+(\.[0-9]+) {return DNR;}
[0-9]+ {return NR;}
['"].+['"] {return STR;}

[ \t] ;
\n {yylineno++;}
. {return yytext[0];}

%{
#include <stdio.h>
#include "y.tab.h"
%}

%%

"const" {return CONST;}
"int"|"float"|"str"|"bool" {return TYPE;}
"true"|"false" {return BOOL;}

"func" {return FUNC;}
"endfunc" {return ENDFUNC;}
"return" {return RETURN;}

"obj" {return OBJ;}
"object" {return OBJECT;}
"endobj" {return ENDOBJ;}
"private" {return PRIVATE;}
"public" {return PUBLIC;}

"if" {return IF;}
"then" {return THEN;}
"elif" {return ELIF;}
"else" {return ELSE;}
"endif" {return ENDIF;}

"while" {return WHILE;}
"endwhile" {return ENDWHILE;}
"break" {return BREAK;}
"continue" {return CONTINUE;}

"+" {return OP_PLUS;}
"-" {return OP_MINUS;}
"*" {return OP_MUL;}
"/" {return OP_DIV;}
">"|"<"|">="|"<="|"=="|"!=" {return OP_COMP;}
"not" {return OP_NOT;}
"and"|"or"|"xor" {return OP_LOGIC;}

"print" {return PRINT;}

\$[_a-zA-Z][_a-zA-Z0-9]* {return ID;}
"=" {return ASSIGN;}

[0-9]+\.[0-9]+ {return DNR;}
[0-9]+ {yylval.value = strtol(yytext, 0, 10); return NR;}
['"][^"']+['"] {return STR;}

[ \t] ;
\n {yylineno++;}
. {return yytext[0];}

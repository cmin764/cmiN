%{
#include <stdio.h>
%}
%start s
%token SMB
%%
s : e {printf("regula s->e \n");}
  ;
e : '(' e '+' e ')' {printf("regula e->(e+e)\n");}
  | '(' e '*' e ')' {printf("regula e->(e*e)\n");}
  |  SMB {printf("regula e->SMB\n");}
  ;
  
%%

int main(){
 yyparse();
}
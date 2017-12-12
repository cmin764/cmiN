%{
#include <stdio.h>
%}
%start s
%token SMB
%%
s : e  {$$=$1;  printf("regula s->e\n valoarea expresiei:%d\n",$$);}
  ;
e : '('e '+' e ')'  {$$=$2+$4;printf("regula e->(e+e)\n"); }
  | '('e '*' e ')'  {$$=$2*$4; printf("regula e->(e*e)\n"); }
  | SMB {$$=$1; printf("regula e->%d\n",$1); }
  ;
  
%%

int main(){
 yyparse();
}

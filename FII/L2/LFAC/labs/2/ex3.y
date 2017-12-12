%{
#include <stdio.h>
%}
%start s
%token SMB

%left '+' '-'
%left '*'

%%
s : e  {$$=$1; printf("s->e\n valoarea expresiei:%d \n",$$);}
  ;
e : e '+' e   {$$=$1+$3;  printf("e->e+e\n");}
  | e '*' e   {$$=$1*$3;  printf("e->e*e\n");}
  | e '-' e   {$$=$1-$3;  printf("e->e-e\n");}
  |'(' e ')' {$$= $2;  printf("e->(e)\n");  }
  | SMB {$$=$1; printf("e->%d\n",$1); }
  ;
  
%%

int main(){
 yyparse();
}

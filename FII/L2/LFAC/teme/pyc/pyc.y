%{
#include <stdio.h>
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
%}

%token ID TYPE ASSIGN CONST
%token NR DNR STR
%token FUNC ENDFUNC RETURN

%start source

%%

source : block {printf("[i] Syntax OK.\n");}
       ;

block :
      | var_decl block
      | const_decl block
      | funcs block
      | statements block
      ;

lit : NR
    | DNR
    | STR
    ;

multi_expr : expr
           | expr ',' multi_expr
           ;

array : '[' ']'
      | '[' multi_expr ']'
      ;

array_access :
             | '[' NR ']' array_access
             ;

expr : lit
     | ID array_access
     | array
     | func_call
     | var_assign
     ;

array_decl :
      | '[' ']' array_decl
      | array_access
      ;

var_assign : ID ASSIGN expr
           ;

var_decl : TYPE array_decl ID
         | TYPE array_decl var_assign
         ;

const_decl : CONST TYPE array_decl var_assign
           ;

param : var_decl
      | const_decl
      ;

req_params : param
           | param ',' req_params
           ;

params :
       | req_params
       ;

funcs : FUNC TYPE array_decl ID '(' params ')' block RETURN expr ENDFUNC
      ;

args : 
     | multi_expr
     ;

func_call : ID '(' args ')'
          ;

statements :
           | var_assign statements
           | func_call statements
           ;

%%

int yyerror(char* s)
{
    printf("[x] Error: %s at line: %d.\n", s, yylineno);
}

int main(int argc, char** argv)
{
    yyin = fopen(argv[1], "r");
    yyparse();
}

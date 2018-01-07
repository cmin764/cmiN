%{
#include <stdio.h>
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
%}

%union {
    long value;
}
%token <value> NR
%type <value> num_expr

%token ID TYPE ASSIGN CONST
%token DNR STR BOOL
%token FUNC ENDFUNC RETURN
%token OBJ OBJECT ENDOBJ PRIVATE PUBLIC
%token IF THEN ELIF ELSE ENDIF
%token WHILE ENDWHILE BREAK CONTINUE
%token OP_PLUS OP_MINUS OP_MUL OP_DIV
%token OP_COMP OP_NOT OP_LOGIC
%token PRINT

%left OP_PLUS OP_MINUS OP_MUL OP_DIV

%start source

%%

source : block {printf("[i] Syntax OK.\n");}
       ;

block :
      | var_decl block
      | const_decl block
      | func_def block
      | obj_def block
      | statements block
      ;


any_type : TYPE
         | OBJECT ID
         ;

lit : NR
    | DNR
    | STR
    | BOOL
    ;

expr : '(' expr ')'
     | arit_expr
     | comp_expr
     | logic_expr
     | str_ops
     | ID array_access
     | array
     | func_call
     | var_assign
     | obj_create
     | lit
     ;

op_arit : OP_PLUS
        | OP_MINUS
        | OP_MUL
        | OP_DIV
        ;

arit_expr : expr op_arit expr
          ;

comp_expr : expr OP_COMP expr
          ;

logic_expr : expr OP_LOGIC expr
           | OP_NOT expr
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

array_decl :
      | '[' ']' array_decl
      | array_access
      ;


var_assign : ID ASSIGN expr
           ;

var_decl : any_type array_decl ID
         | any_type array_decl var_assign
         ;

const_decl : CONST any_type array_decl var_assign
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

func_def : FUNC any_type array_decl ID '(' params ')' block RETURN expr ENDFUNC
         ;

args : 
     | multi_expr
     ;

func_call : ID '(' args ')'
          ;


obj_access : PRIVATE
           | PUBLIC
           ;

obj_member : var_decl
           | const_decl
           | func_def
           ;

obj_members :
            | obj_access ':' obj_member obj_members
            ;

obj_base : ID
         ;

obj_bases : obj_base
          | obj_base ',' obj_bases
          ;

obj_super :
          | '(' obj_bases ')'
          ;

obj_def : OBJ ID obj_super obj_members ENDOBJ
        ;

obj_create : OBJECT ID '(' args ')'
           ;


elif_ctrl : 
          | ELIF expr THEN block
          ;

else_ctrl :
          | ELSE block
          ;

if_ctrl : IF expr THEN block elif_ctrl else_ctrl ENDIF
        ;


loop_ctrl : BREAK
          | CONTINUE
          ;

loop_statements :
                | loop_statements loop_ctrl
                | loop_statements block
                ;

while_loop : WHILE expr loop_statements ENDWHILE
           ;


str_add : STR
        | str_add OP_PLUS STR
        ;

nrs_mul : NR
        | nrs_mul OP_MUL NR
        ;

str_mul : nrs_mul OP_MUL STR OP_MUL nrs_mul
        | STR OP_MUL nrs_mul
        | nrs_mul OP_MUL STR
        ;

str_ops : str_mul
        | str_add
        ;


num_expr : '(' num_expr ')' {$$ = $2;}
         | num_expr OP_PLUS num_expr  {$$ = $1 + $3;}
         | num_expr OP_MINUS num_expr  {$$ = $1 - $3;}
         | num_expr OP_MUL num_expr  {$$ = $1 * $3;}
         | num_expr OP_DIV num_expr  {$$ = $1 / $3;}
         | NR {$$ = $1;}
         ;

print : PRINT '(' num_expr ')' {printf("%d\n", $3);}
      ;


statements :
           | var_assign statements
           | func_call statements
           | if_ctrl
           | while_loop
           | print
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

/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NR = 258,
    ID = 259,
    TYPE = 260,
    ASSIGN = 261,
    CONST = 262,
    DNR = 263,
    STR = 264,
    BOOL = 265,
    FUNC = 266,
    ENDFUNC = 267,
    RETURN = 268,
    OBJ = 269,
    OBJECT = 270,
    ENDOBJ = 271,
    PRIVATE = 272,
    PUBLIC = 273,
    IF = 274,
    THEN = 275,
    ELIF = 276,
    ELSE = 277,
    ENDIF = 278,
    WHILE = 279,
    ENDWHILE = 280,
    BREAK = 281,
    CONTINUE = 282,
    OP_PLUS = 283,
    OP_MINUS = 284,
    OP_MUL = 285,
    OP_DIV = 286,
    OP_COMP = 287,
    OP_NOT = 288,
    OP_LOGIC = 289,
    PRINT = 290
  };
#endif
/* Tokens.  */
#define NR 258
#define ID 259
#define TYPE 260
#define ASSIGN 261
#define CONST 262
#define DNR 263
#define STR 264
#define BOOL 265
#define FUNC 266
#define ENDFUNC 267
#define RETURN 268
#define OBJ 269
#define OBJECT 270
#define ENDOBJ 271
#define PRIVATE 272
#define PUBLIC 273
#define IF 274
#define THEN 275
#define ELIF 276
#define ELSE 277
#define ENDIF 278
#define WHILE 279
#define ENDWHILE 280
#define BREAK 281
#define CONTINUE 282
#define OP_PLUS 283
#define OP_MINUS 284
#define OP_MUL 285
#define OP_DIV 286
#define OP_COMP 287
#define OP_NOT 288
#define OP_LOGIC 289
#define PRINT 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 8 "pyc.y" /* yacc.c:1909  */

    long value;

#line 128 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

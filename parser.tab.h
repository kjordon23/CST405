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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT_T = 258,
    CHAR_T = 259,
    VOID_T = 260,
    FLOAT_T = 261,
    ID = 262,
    PLUS = 263,
    MINUS = 264,
    TIMES = 265,
    DIVIDE = 266,
    SEMICOLON = 267,
    LEFTBRAC = 268,
    RIGHTBRAC = 269,
    EQUAL = 270,
    LEFTCURLY = 271,
    RIGHTCURLY = 272,
    COMMA = 273,
    LEFTPAREN = 274,
    RIGHTPAREN = 275,
    EXCLAMCOND = 276,
    ANDCOND = 277,
    ORCOND = 278,
    LTCOND = 279,
    GTCOND = 280,
    LTECOND = 281,
    GTECOND = 282,
    NOTEQUAL = 283,
    EQCOND = 284,
    WRITELN_T = 285,
    WRITE_T = 286,
    WHILE_T = 287,
    IF_T = 288,
    ELSE_T = 289,
    RETURN_T = 290,
    BREAK_T = 291,
    READ_T = 292,
    NUMBER = 293,
    NUM_FLOAT = 294,
    CHAR_VAL = 295,
    NEG = 296,
    NOTEQUA = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 66 "parser.y" /* yacc.c:1909  */

	Value val;
	sym_entry* symtab_item;
	AST_Node* node;
	int data_type;
	int const_type;
	int array_size;
	Param parameter;

#line 107 "parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

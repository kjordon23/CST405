/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include "symtab.c"
#include "AST.h"
#include "AST.c"
#include "semantics.c"
#include "code_gen.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>	// for time()
#include <unistd.h>	// for sleep()
#define YYDEBUG 1
extern int yylex();
extern FILE *yyin;
extern FILE *yyout;
extern int yylineno;
// for declarations
sym_entry **names;
int name_count = 0;	// number of declarations on line of tokens

// initializing values for arrays
Value *vals;
int value_count = 0;
void yyerror (const char *s) {
	fprintf(stderr, "There is a parse error at line %i: %s\n", yylineno, s);
}

void add_to_names(sym_entry *entry){
	// first entry
	if(name_count == 0){
		name_count = 1;
		names = (sym_entry **) malloc( 1 * sizeof(sym_entry *));
		names[0] = entry;
	}
	// general case
	else{
		name_count++;
		names = (sym_entry **) realloc(names, name_count * sizeof(sym_entry *));
		names[name_count - 1] = entry;		
	}
}

void add_to_vals(Value val){
	// first entry
	if(value_count == 0){
		value_count = 1;
		vals = (Value *) malloc(1 * sizeof(Value));
		vals[0] = val;
	}
	// general case
	else{
		value_count++;
		vals = (Value *) realloc(vals, value_count * sizeof(Value));
		vals[value_count - 1] = val;
	}
}

extern int yydebug; // Only for debugging purposes

// temp variable for functions
AST_Node_Func_Decl *temp_function;

#line 129 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
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
#line 66 "parser.y" /* yacc.c:355  */

	Value val;
	sym_entry* symtab_item;
	AST_Node* node;
	int data_type;
	int const_type;
	int array_size;
	Param parameter;

#line 222 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 239 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   269

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  166

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   109,   109,   109,   109,   115,   119,   122,   126,   126,
     126,   151,   152,   153,   154,   158,   162,   175,   183,   191,
     198,   213,   218,   226,   227,   228,   229,   235,   239,   244,
     248,   249,   250,   251,   252,   253,   254,   255,   259,   263,
     264,   268,   280,   287,   288,   292,   296,   313,   330,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   384,   391,   447,   459,   515,   520,   530,
     535,   544,   549,   555,   560,   567,   567,   577,   578,   577,
     605,   609,   610,   611,   616,   621,   628,   628,   646,   650,
     657,   664,   669,   676,   677,   678,   679
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_T", "CHAR_T", "VOID_T", "FLOAT_T",
  "ID", "PLUS", "MINUS", "TIMES", "DIVIDE", "SEMICOLON", "LEFTBRAC",
  "RIGHTBRAC", "EQUAL", "LEFTCURLY", "RIGHTCURLY", "COMMA", "LEFTPAREN",
  "RIGHTPAREN", "EXCLAMCOND", "ANDCOND", "ORCOND", "LTCOND", "GTCOND",
  "LTECOND", "GTECOND", "NOTEQUAL", "EQCOND", "WRITELN_T", "WRITE_T",
  "WHILE_T", "IF_T", "ELSE_T", "RETURN_T", "BREAK_T", "READ_T", "NUMBER",
  "NUM_FLOAT", "CHAR_VAL", "NEG", "NOTEQUA", "$accept", "prog", "$@1",
  "$@2", "VarDecList", "VarDecl", "$@3", "$@4", "decNames", "var", "array",
  "initVar", "values", "Type", "stmtList", "stmt", "readStatement",
  "writeStatement", "whileStatement", "decisionStatement", "ElseStatement",
  "Block", "Expr", "assign", "var_ref", "funcCall", "funcCallParams",
  "funcCallParam", "FuncDecListOptional", "FuncDecList", "FuncDecl", "$@5",
  "FuncDeclHead", "$@6", "$@7", "FuncType", "ParamDecList",
  "ParamDecListTail", "ParamDecl", "$@8", "FuncDeclTail", "FuncVarDecs",
  "FuncStatements", "FuncReturn", "Const", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297
};
# endif

#define YYPACT_NINF -104

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-104)))

#define YYTABLE_NINF -84

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      64,  -104,  -104,  -104,  -104,     9,    64,  -104,  -104,  -104,
      82,  -104,    16,    -1,    82,    27,     8,    23,    24,    34,
      30,  -104,    82,  -104,  -104,  -104,  -104,  -104,  -104,    46,
      35,    59,    13,    54,  -104,  -104,    15,    38,  -104,   127,
    -104,    67,    38,    38,  -104,    67,    75,  -104,  -104,    38,
    -104,    26,    66,    16,    70,    26,    38,    38,    65,  -104,
    -104,   157,  -104,  -104,  -104,  -104,   219,    63,    83,  -104,
      71,    80,   167,   189,    85,  -104,   102,  -104,  -104,   219,
      26,  -104,    87,  -104,  -104,  -104,  -104,   211,    88,  -104,
      38,    38,    38,    38,  -104,    38,    38,    38,    38,    38,
      38,    38,    38,  -104,    38,    99,   101,   101,   117,  -104,
     115,    64,  -104,    26,  -104,    88,    88,    88,    88,   241,
     241,    52,    52,    52,    52,   219,   241,   219,  -104,  -104,
     105,  -104,    64,  -104,  -104,   128,     2,  -104,   101,  -104,
      64,    82,   121,  -104,    26,  -104,    82,   107,  -104,  -104,
      38,   119,     5,    98,  -104,  -104,   126,   129,  -104,    64,
    -104,  -104,  -104,    67,  -104,  -104
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       7,    23,    24,    26,    25,     0,     2,     6,     8,     1,
      29,     5,     0,    15,    29,     0,     0,     0,     0,     0,
       0,    65,     3,    27,    31,    32,    33,    34,    37,     0,
       0,     0,    15,     9,    13,    14,     0,    68,    16,     0,
      40,     0,     0,     0,    35,     0,    75,    28,    30,     0,
      36,     0,    16,     0,     0,     0,     0,     0,    93,    94,
      95,     0,    60,    63,    61,    93,    70,     0,    67,    45,
      15,     0,     0,     0,     0,     4,    75,    74,    77,    64,
       0,    19,     0,    11,    12,    10,    62,     0,    54,    18,
       0,     0,     0,     0,    17,     0,     0,     0,     0,     0,
       0,     0,     0,    66,     0,     0,     0,     0,     0,    73,
       0,     0,    96,     0,    59,    46,    47,    48,    49,    53,
      52,    55,    56,    57,    58,    51,    50,    69,    39,    41,
      44,    38,     7,    76,    80,     0,     0,    22,     0,    42,
      89,    29,     0,    20,     0,    43,    90,    92,    78,    21,
       0,     0,    86,     0,    88,    82,     0,    81,    85,     0,
      91,    79,    86,     0,    84,    87
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -104,  -104,  -104,  -104,    17,     1,  -104,  -104,  -104,   -12,
     116,    97,  -104,  -103,   -11,   -18,  -104,  -104,  -104,  -104,
    -104,   -90,    -5,  -104,    -9,    -8,  -104,  -104,  -104,  -104,
      76,  -104,  -104,  -104,  -104,  -104,  -104,  -104,    -7,  -104,
    -104,  -104,  -104,  -104,   -40
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,    10,    46,     6,     7,    12,    54,    33,    21,
      38,    35,   136,     8,    22,    23,    24,    25,    26,    27,
     139,    28,    61,    29,    62,    63,    67,    68,    75,    76,
      77,    78,   110,   111,   152,   135,   156,   157,   158,   159,
     133,   141,   147,   151,    64
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      34,    30,    31,    39,    47,    30,    31,    11,   134,     9,
     155,    81,    36,    30,    31,    86,   129,   130,    37,   143,
     144,    47,    13,    32,    55,   -83,    36,    41,    51,    71,
      30,    31,    66,    74,    56,    80,    57,    72,    73,    40,
     112,    83,    42,    43,    79,    13,    44,    55,   145,    45,
      49,    87,    88,    58,    59,    60,   163,    56,    48,    57,
      90,    91,    92,    93,    65,    59,    60,     1,     2,     3,
       4,    50,    53,   137,    70,   -72,    65,    59,    60,    89,
     101,    82,    85,   103,    36,   115,   116,   117,   118,    13,
     119,   120,   121,   122,   123,   124,   125,   126,    14,   127,
     105,   104,   -71,   113,   149,   108,    90,    91,    92,    93,
     160,   128,    15,    16,    17,    18,   101,    14,    19,    20,
      95,    96,    97,    98,    99,   100,   101,   102,    47,   131,
     146,   132,    30,    31,    13,   142,   154,    30,    31,   138,
     148,    11,   150,    14,    69,   153,   161,   162,    52,   140,
      84,   165,   109,     0,     0,   164,     0,    15,    16,    17,
      18,     0,     0,    19,    20,    90,    91,    92,    93,     0,
       0,    94,     0,     0,     0,    90,    91,    92,    93,    95,
      96,    97,    98,    99,   100,   101,   102,   106,     0,    95,
      96,    97,    98,    99,   100,   101,   102,    90,    91,    92,
      93,     0,     0,     0,     0,     0,     0,     0,     0,   107,
       0,    95,    96,    97,    98,    99,   100,   101,   102,    90,
      91,    92,    93,     0,     0,     0,     0,    90,    91,    92,
      93,   114,     0,    95,    96,    97,    98,    99,   100,   101,
     102,    95,    96,    97,    98,    99,   100,   101,   102,    90,
      91,    92,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    97,    98,    99,   100,   101
};

static const yytype_int16 yycheck[] =
{
      12,    10,    10,    14,    22,    14,    14,     6,   111,     0,
       5,    51,    13,    22,    22,    55,   106,   107,    19,    17,
      18,    39,     7,     7,     9,    20,    13,    19,    15,    41,
      39,    39,    37,    45,    19,     9,    21,    42,    43,    12,
      80,    53,    19,    19,    49,     7,    12,     9,   138,    19,
      15,    56,    57,    38,    39,    40,   159,    19,    12,    21,
       8,     9,    10,    11,    38,    39,    40,     3,     4,     5,
       6,    12,    18,   113,     7,     0,    38,    39,    40,    14,
      28,    15,    12,    20,    13,    90,    91,    92,    93,     7,
      95,    96,    97,    98,    99,   100,   101,   102,    16,   104,
      20,    18,     0,    16,   144,    20,     8,     9,    10,    11,
      12,    12,    30,    31,    32,    33,    28,    16,    36,    37,
      22,    23,    24,    25,    26,    27,    28,    29,   146,    12,
     141,    16,   141,   141,     7,     7,    17,   146,   146,    34,
      19,   140,    35,    16,    17,   150,    20,    18,    32,   132,
      53,   163,    76,    -1,    -1,   162,    -1,    30,    31,    32,
      33,    -1,    -1,    36,    37,     8,     9,    10,    11,    -1,
      -1,    14,    -1,    -1,    -1,     8,     9,    10,    11,    22,
      23,    24,    25,    26,    27,    28,    29,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,    29,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    22,    23,    24,    25,    26,    27,    28,    29,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,     8,     9,    10,
      11,    20,    -1,    22,    23,    24,    25,    26,    27,    28,
      29,    22,    23,    24,    25,    26,    27,    28,    29,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,    28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,    44,    47,    48,    56,     0,
      45,    48,    49,     7,    16,    30,    31,    32,    33,    36,
      37,    52,    57,    58,    59,    60,    61,    62,    64,    66,
      67,    68,     7,    51,    52,    54,    13,    19,    53,    57,
      12,    19,    19,    19,    12,    19,    46,    58,    12,    15,
      12,    15,    53,    18,    50,     9,    19,    21,    38,    39,
      40,    65,    67,    68,    87,    38,    65,    69,    70,    17,
       7,    52,    65,    65,    52,    71,    72,    73,    74,    65,
       9,    87,    15,    52,    54,    12,    87,    65,    65,    14,
       8,     9,    10,    11,    14,    22,    23,    24,    25,    26,
      27,    28,    29,    20,    18,    20,    20,    20,    20,    73,
      75,    76,    87,    16,    20,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    12,    64,
      64,    12,    16,    83,    56,    78,    55,    87,    34,    63,
      47,    84,     7,    17,    18,    64,    57,    85,    19,    87,
      35,    86,    77,    65,    17,     5,    79,    80,    81,    82,
      12,    20,    18,    56,    81,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    45,    46,    44,    47,    47,    47,    49,    50,
      48,    51,    51,    51,    51,    52,    52,    53,    53,    54,
      54,    55,    55,    56,    56,    56,    56,    57,    57,    57,
      58,    58,    58,    58,    58,    58,    58,    58,    59,    60,
      60,    61,    62,    63,    63,    64,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    66,    67,    68,    69,    69,    70,
      70,    71,    71,    72,    72,    74,    73,    76,    77,    75,
      78,    79,    79,    79,    80,    80,    82,    81,    83,    84,
      85,    86,    86,    87,    87,    87,    87
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     5,     2,     1,     0,     0,     0,
       5,     3,     3,     1,     1,     1,     2,     3,     3,     3,
       6,     3,     1,     1,     1,     1,     1,     1,     2,     0,
       2,     1,     1,     1,     1,     2,     2,     1,     5,     5,
       2,     5,     6,     2,     0,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     3,     3,
       1,     1,     2,     1,     3,     1,     4,     1,     0,     3,
       1,     1,     0,     2,     1,     0,     3,     0,     0,     7,
       1,     1,     1,     0,     3,     1,     0,     3,     5,     1,
       1,     3,     0,     1,     1,     1,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 109 "parser.y" /* yacc.c:1646  */
    { ast_traversal((yyvsp[0].node)); }
#line 1460 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 109 "parser.y" /* yacc.c:1646  */
    { ast_traversal((yyvsp[0].node)); }
#line 1466 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 109 "parser.y" /* yacc.c:1646  */
    { ast_traversal((yyvsp[0].node)); }
#line 1472 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 115 "parser.y" /* yacc.c:1646  */
    {
		AST_Node_Declarations *temp = (AST_Node_Declarations*) (yyvsp[-1].node);
		(yyval.node) = new_declarations_node(temp->declarations, temp->declaration_count, (yyvsp[0].node));
	}
#line 1481 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 119 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = new_declarations_node(NULL, 0, (yyvsp[0].node));
	}
#line 1489 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 122 "parser.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1495 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 126 "parser.y" /* yacc.c:1646  */
    {declare = 1;}
#line 1501 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 126 "parser.y" /* yacc.c:1646  */
    {declare = 0;}
#line 1507 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 127 "parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[-4].data_type) == VOID_TYPE) {
			yyerror("Void is not a correct variable type");
			exit(1);
		}

		(yyval.node) = new_ast_decl_node((yyvsp[-4].data_type), names, name_count);
		name_count = 0;

		AST_Node_Decl *tempDec = (AST_Node_Decl* ) (yyval.node);

		// declare the types of the variables being declared
		for (int i = 0; i < tempDec->names_count; i++) {
			if (tempDec->names[i]->sym_type == UNDEF) {
				set_type(tempDec->names[i]->name, tempDec->data_type, UNDEF);
			}
			else if (tempDec->names[i]->sym_type == ARRAY_TYPE) {
				set_type(tempDec->names[i]->name, ARRAY_TYPE, tempDec->data_type);
			}
		}
	}
#line 1533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 151 "parser.y" /* yacc.c:1646  */
    {add_to_names((yyvsp[0].symtab_item));}
#line 1539 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 152 "parser.y" /* yacc.c:1646  */
    {add_to_names((yyvsp[0].symtab_item));}
#line 1545 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 153 "parser.y" /* yacc.c:1646  */
    {add_to_names((yyvsp[0].symtab_item));}
#line 1551 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 154 "parser.y" /* yacc.c:1646  */
    {add_to_names((yyvsp[0].symtab_item));}
#line 1557 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 159 "parser.y" /* yacc.c:1646  */
    {
		(yyval.symtab_item) = (yyvsp[0].symtab_item);
	}
#line 1565 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 163 "parser.y" /* yacc.c:1646  */
    {
		if (declare == 1) 
		{
			(yyvsp[-1].symtab_item)->sym_type = ARRAY_TYPE;
			(yyvsp[-1].symtab_item)->array_size = (yyvsp[0].array_size);
			(yyvsp[-1].symtab_item)->vals = NULL;
			(yyval.symtab_item) = (yyvsp[-1].symtab_item);
		}
	}
#line 1579 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 176 "parser.y" /* yacc.c:1646  */
    {
		// Syntax error if the declaration contains an expression
		if (declare == 1) {
			yyerror("Array cannot contain an expression\nExiting Program\n");
			exit(1);
		}
	}
#line 1591 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 184 "parser.y" /* yacc.c:1646  */
    {
		// Pass in the size from the number token
		(yyval.array_size) = (yyvsp[-1].val).ival;
	}
#line 1600 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 192 "parser.y" /* yacc.c:1646  */
    {
		AST_Node_Const *tempCons = (AST_Node_Const*) (yyvsp[0].node);
		(yyvsp[-2].symtab_item)->val = tempCons->val;
		(yyvsp[-2].symtab_item)->sym_type = tempCons->const_type;
		(yyval.symtab_item) = (yyvsp[-2].symtab_item);
	}
#line 1611 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 199 "parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[-4].array_size) != value_count) {
			fprintf(stderr, "Semantic Error at line %d: Initialized Array does not contain the right amount of values", yylineno);
			exit(1);
		}
		(yyvsp[-5].symtab_item)->sym_type = ARRAY_TYPE;
		(yyvsp[-5].symtab_item)->array_size = (yyvsp[-4].array_size);
		(yyvsp[-5].symtab_item)->vals = vals;
		(yyval.symtab_item) = (yyvsp[-5].symtab_item);
		value_count = 0;
	}
#line 1627 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 214 "parser.y" /* yacc.c:1646  */
    {
		AST_Node_Const *temp = (AST_Node_Const*) (yyvsp[0].node);
		add_to_vals(temp->val);
	}
#line 1636 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 219 "parser.y" /* yacc.c:1646  */
    {
		AST_Node_Const *temp = (AST_Node_Const*) (yyvsp[0].node);
		add_to_vals(temp->val);
	}
#line 1645 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 226 "parser.y" /* yacc.c:1646  */
    {(yyval.data_type) = INT_TYPE;}
#line 1651 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 227 "parser.y" /* yacc.c:1646  */
    {(yyval.data_type) = CHAR_TYPE;}
#line 1657 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 228 "parser.y" /* yacc.c:1646  */
    {(yyval.data_type) = FLOAT_TYPE;}
#line 1663 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 229 "parser.y" /* yacc.c:1646  */
    {(yyval.data_type) = VOID_TYPE;}
#line 1669 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 236 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = new_statements_node(NULL, 0, (yyvsp[0].node));
	}
#line 1677 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 240 "parser.y" /* yacc.c:1646  */
    {
		AST_Node_Statements *tempState = (AST_Node_Statements*) (yyvsp[-1].node);
		(yyval.node) = new_statements_node(tempState->statements, tempState->statement_count, (yyvsp[0].node));
	}
#line 1686 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 244 "parser.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1692 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 248 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1698 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 249 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1704 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 250 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1710 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 251 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1716 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 252 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1722 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 253 "parser.y" /* yacc.c:1646  */
    {(yyval.node) = new_ast_simple_node(1);}
#line 1728 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 254 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1734 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 255 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1740 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 259 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_read_node((yyvsp[-2].symtab_item), (yyvsp[-2].symtab_item)->val); }
#line 1746 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 263 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_write_node((yyvsp[-2].symtab_item));}
#line 1752 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 264 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_writeln_node(); }
#line 1758 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 269 "parser.y" /* yacc.c:1646  */
    { 
		(yyval.node) = new_ast_while_node((yyvsp[-2].node), (yyvsp[0].node));
		if ((yyvsp[-2].node)->type == BOOL_NODE || (yyvsp[-2].node)->type == REL_NODE || (yyvsp[-2].node)->type == EQU_NODE) {
			printf("{Optimization Opportunity (Loop Unrolling)} Loop Unrolling can occur at line %d, which means that we can repeat the block of code inside if statement until the condition has been met\n", yylineno);
		}
	}
#line 1769 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 281 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = new_ast_if_node((yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
	}
#line 1777 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 287 "parser.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1783 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 288 "parser.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1789 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 292 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1795 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 297 "parser.y" /* yacc.c:1646  */
    { 
		(yyval.node) = new_ast_arithm_node(ADD_OP, (yyvsp[-2].node), (yyvsp[0].node));
		if ((yyvsp[0].node)->type == CONST_NODE) {
			if (((AST_Node_Const*)(yyvsp[0].node))->val.ival == 0 || ((AST_Node_Const*)(yyvsp[0].node))->val.fval == 0) {
				printf("{Optimization Opportunity (Algebraic Simplification)} There is no need to generate code for the addition at line %d since you are only adding by 0\n", yylineno);
			}
		} 
        else if ((yyvsp[-2].node)->type == CONST_NODE) {
			if (((AST_Node_Const*)(yyvsp[-2].node))->val.ival == 0 || ((AST_Node_Const*)(yyvsp[-2].node))->val.fval == 0) {
				printf("{Optimization Opportunity (Algebraic Simplification)} There is no need to generate code for the addition at line %d since you are only adding by 0\n", yylineno);
			}
		}
        if ((yyvsp[-2].node)->type == CONST_NODE && (yyvsp[0].node)->type == CONST_NODE){
            printf("{Optimization Opportunity (Constant Folding)} You can perform the arithmetic on line %d insde the semantic analyzer, and then you would only have to pass in a constant node without having to generate code for the arithmetic.\n", yylineno);
        }
	}
#line 1816 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 314 "parser.y" /* yacc.c:1646  */
    { 
		(yyval.node) = new_ast_arithm_node(SUB_OP, (yyvsp[-2].node), (yyvsp[0].node)); 
		if ((yyvsp[0].node)->type == CONST_NODE) {
			if (((AST_Node_Const*)(yyvsp[0].node))->val.ival == 0 || ((AST_Node_Const*)(yyvsp[0].node))->val.fval == 0) {
				printf("{Optimization Opportunity (Algebraic Simplification)} There is no need to generate code for the addition at line %d since you are only subtracting by 0\n", yylineno);
			}
		} 
        else if ((yyvsp[-2].node)->type == CONST_NODE) {
			if (((AST_Node_Const*)(yyvsp[-2].node))->val.ival == 0 || ((AST_Node_Const*)(yyvsp[-2].node))->val.fval == 0) {
				printf("{Optimization Opportunity (Algebraic Simplification)} There is no need to generate code for the addition at line %d since you are only subtracting by 0\n", yylineno);
			}
		}
        if ((yyvsp[-2].node)->type == CONST_NODE && (yyvsp[0].node)->type == CONST_NODE){
            printf("{Optimization Opportunity (Constant Folding)} You can perform the arithmetic on line %d insde the semantic analyzer, and then you would only have to pass in a constant node without having to generate code for the arithmetic.\n", yylineno);
        }
	}
#line 1837 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 331 "parser.y" /* yacc.c:1646  */
    { 
		(yyval.node) = new_ast_arithm_node(MUL_OP, (yyvsp[-2].node), (yyvsp[0].node));
		if ((yyvsp[0].node)->type == CONST_NODE) {
			if (((AST_Node_Const*)(yyvsp[0].node))->val.ival == 1 || ((AST_Node_Const*)(yyvsp[0].node))->val.fval == 1) {
				printf("{Optimization Opportunity (Algebraic Simplification)} There is no need to generate code for the addition at line %d since you are only multiplying by 1\n", yylineno);
			}
            else if (((AST_Node_Const*)(yyvsp[0].node))->val.ival > 1) {
				printf("{Optimization Opportunity (Strength Reduction)} At line %d, You can add the multiplier %d times to eliminate operations that have a heavy cost.\n", yylineno, ((AST_Node_Const*)(yyvsp[0].node))->val.ival);
			}
		} 
        else if ((yyvsp[-2].node)->type == CONST_NODE) {
			if (((AST_Node_Const*)(yyvsp[-2].node))->val.ival == 1 || ((AST_Node_Const*)(yyvsp[-2].node))->val.fval == 1) {
				printf("{Optimization Opportunity (Algebraic Simplification)} There is no need to generate code for the addition at line %d since you are only multiplying by 1\n", yylineno);
			}
            else if (((AST_Node_Const*)(yyvsp[0].node))->val.ival > 1) {
				printf("{Optimization Opportunity (Strength Reduction)} At line %d, You can add the multiplier %d times to eliminate operations that have a heavy cost.\n", yylineno, ((AST_Node_Const*)(yyvsp[0].node))->val.ival);
			}
		} 
        if ((yyvsp[-2].node)->type == CONST_NODE && (yyvsp[0].node)->type == CONST_NODE){
            printf("{Optimization Opportunity (Constant Folding)} You can perform the arithmetic on line %d insde the semantic analyzer, and then you would only have to pass in a constant node without having to generate code for the arithmetic.\n", yylineno);
        }
	}
#line 1864 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 353 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_arithm_node(DIV_OP, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1870 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 354 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_equ_node(EQUAL_COND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1876 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 355 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_equ_node(NOT_EQUAL_COND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1882 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 356 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_bool_node(OR_COND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1888 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 357 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_bool_node(AND_COND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1894 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 358 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_bool_node(NOT_COND, (yyvsp[0].node), NULL); }
#line 1900 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 359 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_rel_node(LESS_COND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1906 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 360 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_rel_node(GREATER_COND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1912 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 361 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_rel_node(LESS_EQUAL_COND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1918 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 362 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_rel_node(GREATER_EQUAL_COND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1924 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 363 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1930 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 364 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1936 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 365 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1942 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 367 "parser.y" /* yacc.c:1646  */
    {
		AST_Node_Const *tempConst = (AST_Node_Const*) (yyvsp[0].node);
		switch(tempConst->const_type) {
			case INT_TYPE:
				tempConst->val.ival *= -1;
				break;
			case FLOAT_T:
				tempConst->val.fval *= -1;
				break;
			case CHAR_TYPE:
				yyerror("Error having a negative sign in front of a char variable");
				exit(1);
				break;
		}

		(yyval.node) = (AST_Node *) tempConst;
	}
#line 1964 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 385 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = (yyvsp[0].node);
	}
#line 1972 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 392 "parser.y" /* yacc.c:1646  */
    {
		AST_Node_Ref *tempRef = (AST_Node_Ref*) (yyvsp[-2].node);
		(yyval.node) = new_ast_assign_node(tempRef->entry, (yyvsp[0].node));
		// Optimization Here, Redundant Expression elimination, Get rid of when we have expression equal to each other
		if ((yyvsp[-2].node)->type == REF_NODE && (yyvsp[0].node)->type == REF_NODE) {
			if (((AST_Node_Ref*)(yyvsp[-2].node))->entry->name == ((AST_Node_Ref*)(yyvsp[0].node))->entry->name) {
				printf("{Optimization Opportunity (Redundant Expressions)} Entries is the same on both sides of the equal in line %d, which means it can be ignored when in the code generation stage\n", yylineno);
			}
		}	
		/* find datatypes */
		int type1 = get_type(tempRef->entry->name);
		int type2 = expression_data_type((yyvsp[0].node));

		/* the last function will give us information about revisits */

		/* contains revisit => add assignment-check to revisit queue */
		if(cont_revisit == 1){	
			/* search if entry exists */
			revisit_queue *q = search_queue(tempRef->entry->name);
			if(q == NULL){
				add_to_queue(tempRef->entry, tempRef->entry->name, ASSIGN_CHECK);
				q = search_queue(tempRef->entry->name);	
			}

			/* setup structures */
			if(q->num_of_assigns == 0){ /* first node */
				q->nodes = (void**) malloc(sizeof(void*));
			}
			else{ /* general case */
				q->nodes = (void**) realloc(q->nodes, (q->num_of_assigns + 1) * sizeof(void*));
			}

			/* add info of assignment */
			q->nodes[q->num_of_assigns] = (void*) (yyvsp[0].node);

			/* increment number of assignments */
			q->num_of_assigns++;

			/* reset revisit flag */
			cont_revisit = 0;

			printf("Assignment revisit for %s at line %d\n", tempRef->entry->name, yylineno);
		}
		else{ /* no revisit */
			/* check assignment semantics */
			get_result_type(
				type1,       /*  variable datatype  */
				type2,       /* expression datatype */
				ISEQUAL  /* checking compatibility only (no operator) */
			);
		}
	}
#line 2029 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 448 "parser.y" /* yacc.c:1646  */
    {
		// Even though it is still shown in symbol table, compiler will not execute code if entry not declared with type
		if ((yyvsp[0].symtab_item)->sym_type == NULL) {
			fprintf(stderr, "Semantic Error at line %d: Variable %s has not been declared yet.\nExiting Program\n", yylineno, (yyvsp[0].symtab_item)->name); 
			exit(1);
		}
		(yyval.node) = new_ast_ref_node((yyvsp[0].symtab_item));
	}
#line 2042 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 460 "parser.y" /* yacc.c:1646  */
    {
		AST_Node_Call_Params *tempParams = (AST_Node_Call_Params*) (yyvsp[-1].node);
		(yyval.node) = new_ast_func_call_node((yyvsp[-3].symtab_item), tempParams->params, tempParams->num_of_pars);

		revisit_queue *q = search_queue((yyvsp[-3].symtab_item)->name);
		if (q != NULL){
			/* setup structures */
			if(q->num_of_calls == 0){ /* first call */
				q->par_types = (int**) malloc(sizeof(int*));
				q->num_of_pars = (int*) malloc(sizeof(int));
			}
			else { /* general case */
				q->par_types = (int**) realloc(q->par_types, (q->num_of_calls + 1) * sizeof(int*));
				q->num_of_pars = (int*) realloc(q->num_of_pars, (q->num_of_calls + 1) * sizeof(int));
			}
		
			/* add info of function call */
			q->num_of_pars[q->num_of_calls] = tempParams->num_of_pars;
			q->par_types[q->num_of_calls] = (int*) malloc(tempParams->num_of_pars * sizeof(int));
			/* get the types of the parameters */
			for(int i = 0; i < tempParams->num_of_pars; i++){
				/* get datatype of parameter-expression */
				q->par_types[q->num_of_calls][i] = expression_data_type(tempParams->params[i]);
			}
		
			/* increment number of calls */
			q->num_of_calls++;
		}
		else{
			/* function declared before call */
			if((yyvsp[-3].symtab_item)->sym_type == FUNCTION_TYPE){
				/* check number of parameters */
				if((yyvsp[-3].symtab_item)->num_of_pars != tempParams->num_of_pars){
					fprintf(stderr, "Function call of %s has wrong num of parameters!\n", (yyvsp[-3].symtab_item)->name);
					exit(1);
				}
				/* check if parameters are compatible */
				for(int i = 0; i < tempParams->num_of_pars; i++){
					/* type of parameter in function declaration */
					int type_1 = expression_data_type(tempParams->params[i]);
				
					/* type of parameter in function call*/
					int type_2 = (yyvsp[-3].symtab_item)->parameters[i].par_type;
				
					/* check compatibility for function call */
					get_result_type(type_1, type_2, ISEQUAL);
					/* error occurs automatically in the function */
				}
			}
		}
	}
#line 2098 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 516 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = (yyvsp[0].node);
	}
#line 2106 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 520 "parser.y" /* yacc.c:1646  */
    {
		AST_Node_Call_Params *tempParams = malloc (sizeof (AST_Node_Call_Params));
		tempParams->type = CALL_PARAMS;
		tempParams->params = NULL;
		tempParams->num_of_pars = 0;
		(yyval.node) = (AST_Node*)tempParams;
	}
#line 2118 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 531 "parser.y" /* yacc.c:1646  */
    {
		AST_Node_Call_Params *tempParams = (AST_Node_Call_Params*) (yyvsp[-2].node);
		(yyval.node) = new_ast_call_params_node(tempParams->params, tempParams->num_of_pars, (yyvsp[0].node));
	}
#line 2127 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 536 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = new_ast_call_params_node(NULL, 0, (yyvsp[0].node));
	}
#line 2135 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 545 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = (yyvsp[0].node);
	}
#line 2143 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 549 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = NULL;
	}
#line 2151 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 556 "parser.y" /* yacc.c:1646  */
    {
		AST_Node_Func_Declarations *tempFunc = (AST_Node_Func_Declarations*) (yyvsp[-1].node);
		(yyval.node) = new_func_declarations_node(tempFunc->func_declarations, tempFunc->func_declaration_count, (yyvsp[0].node));
	}
#line 2160 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 561 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = new_func_declarations_node(NULL, 0, (yyvsp[0].node));
	}
#line 2168 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 567 "parser.y" /* yacc.c:1646  */
    {incr_scope();}
#line 2174 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 568 "parser.y" /* yacc.c:1646  */
    {
		revisit(temp_function->entry->name);

		hide_scope();
		(yyval.node) = (AST_Node *) temp_function;
	}
#line 2185 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 577 "parser.y" /* yacc.c:1646  */
    {declare_func = 1;}
#line 2191 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 578 "parser.y" /* yacc.c:1646  */
    {
		// Optimization Here, Dead Code Elimination
		if (lookup_func_call((yyvsp[-1].symtab_item)->name) == NULL) {
			printf("{Optimization Opportunity (Dead Code Elimination)} No function call for method '%s' at line %d, will eliminate code for entire function in code generation\n", (yyvsp[-1].symtab_item)->name, yylineno);
		}
		declare_func = 0;
		AST_Node_Ret_Type *tempRet = (AST_Node_Ret_Type *) (yyvsp[-2].node);
		temp_function = (AST_Node_Func_Decl *) new_ast_func_decl_node (tempRet->ret_type, (yyvsp[-1].symtab_item));
		temp_function->entry->sym_type = FUNCTION_TYPE;
		temp_function->entry->inf_type = tempRet->ret_type;
	}
#line 2207 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 590 "parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[-1].node) != NULL) {
			AST_Node_Decl_Params *tempParams = (AST_Node_Decl_Params *) (yyvsp[-1].node);

			temp_function->entry->parameters = tempParams->parameters;
			temp_function->entry->num_of_pars = tempParams->num_of_pars;
		}
		else {
			temp_function->entry->parameters = NULL;
			temp_function->entry->num_of_pars = 0;
		}
	}
#line 2224 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 605 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_ret_type_node((yyvsp[0].data_type)); }
#line 2230 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 609 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node);}
#line 2236 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 610 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 2242 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 611 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = NULL;}
#line 2248 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 617 "parser.y" /* yacc.c:1646  */
    {
		AST_Node_Decl_Params *tempParams = (AST_Node_Decl_Params *) (yyvsp[-2].node);
		(yyval.node) = new_ast_decl_params_node(tempParams->parameters, tempParams->num_of_pars, (yyvsp[0].parameter));
	}
#line 2257 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 622 "parser.y" /* yacc.c:1646  */
    {
		(yyval.node) = new_ast_decl_params_node(NULL, 0, (yyvsp[0].parameter));
	}
#line 2265 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 628 "parser.y" /* yacc.c:1646  */
    { declare = 1; }
#line 2271 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 629 "parser.y" /* yacc.c:1646  */
    {
		declare = 0;

		// Setting the type of the parameter
		if ((yyvsp[0].symtab_item)->sym_type == UNDEF) {
			set_type((yyvsp[0].symtab_item)->name, (yyvsp[-1].data_type), UNDEF);
		}
		else if ((yyvsp[0].symtab_item)->sym_type == ARRAY_TYPE) {
			set_type((yyvsp[0].symtab_item)->name, ARRAY_TYPE, (yyvsp[-1].data_type));
		}

		// Defining the parameter that is passed
		(yyval.parameter) = def_param((yyvsp[-1].data_type), (yyvsp[0].symtab_item)->name);
	}
#line 2290 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 646 "parser.y" /* yacc.c:1646  */
    { /* Used to recognize rule in bison */}
#line 2296 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 651 "parser.y" /* yacc.c:1646  */
    {
		temp_function->declarations = (yyvsp[0].node);
	}
#line 2304 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 658 "parser.y" /* yacc.c:1646  */
    {
		temp_function->statements = (yyvsp[0].node);
	}
#line 2312 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 665 "parser.y" /* yacc.c:1646  */
    {
		temp_function->return_node = new_ast_return_node(temp_function->ret_type, (yyvsp[-1].node));
	}
#line 2320 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 669 "parser.y" /* yacc.c:1646  */
    {
		temp_function->return_node = NULL;
	}
#line 2328 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 676 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_const_node(INT_TYPE, (yyvsp[0].val)); }
#line 2334 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 677 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_const_node(FLOAT_TYPE, (yyvsp[0].val)); }
#line 2340 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 678 "parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_const_node(CHAR_TYPE, (yyvsp[0].val)); }
#line 2346 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 680 "parser.y" /* yacc.c:1646  */
    {
		AST_Node_Const *tempConst = (AST_Node_Const*) (yyvsp[0].node);
		switch(tempConst->const_type) {
			case INT_TYPE:
				tempConst->val.ival *= -1;
				break;
			case FLOAT_T:
				tempConst->val.fval *= -1;
				break;
			case CHAR_TYPE:
				yyerror("Error having a negative sign in front of a char variable");
				exit(1);
				break;
		}

		(yyval.node) = (AST_Node *) tempConst;
	}
#line 2368 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2372 "parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 699 "parser.y" /* yacc.c:1906  */


int main(int argc, char **argv)
{
	/*#if YYDEBUG		// Only for debugging purposes
	yydebug = 1;
	#endif*/
	time_t begin  = time(NULL);
	init_hash_table();
	yyin = fopen("text.gcupl", "r");
	printf("Lexical Analysis Done\n\nParse Tree Initiated\n\n");
	yyparse();	// Handles all of the parsing for each of the rules defined
	fclose(yyin);
	printf("\nSyntax Analysis Done\n");
	
	/* perform the semantic checks (assignments) */
	if(queue != NULL){
		revisit_queue *cur;
		cur = queue;
		while(cur != NULL){
			if(cur->revisit_type == ASSIGN_CHECK){
				revisit(cur->name);
			}
			cur = cur->next;
		}
	}
	yyout = fopen("symbolTable.txt", "w");
	if (yyout == NULL) {
		printf("Empty File");
	}
	symtab_dump(yyout);
	fclose(yyout);
	// revisit queue dump
	yyout = fopen("revisit_dump.out", "w");
	if (yyout == NULL) {
		printf("Empty File");
	}
	revisit_dump(yyout);
	/* if still not empty -> Warning */
	if(queue != NULL){
		printf("Warning: Something has not been checked in the revisit queue!\n");
	}
	fclose(yyout);
	generate_code();
	sleep(3);
	time_t end = time(NULL);
	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Time elasped is %f seconds\n", time_spent);
	return 0;
}

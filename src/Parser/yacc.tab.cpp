/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VALUE_INT = 258,
     VALUE_STRING = 259,
     IDENTIFIER = 260,
     OPERATOR = 261,
     DATABASE = 262,
     DATABASES = 263,
     DROP = 264,
     USE = 265,
     INSERT = 266,
     INTO = 267,
     UPDATE = 268,
     SET = 269,
     DESC = 270,
     REFERENCES = 271,
     INDEX = 272,
     TABLE = 273,
     TABLES = 274,
     SHOW = 275,
     CREATE = 276,
     PRIMARY = 277,
     KEY = 278,
     NOT = 279,
     MYNULL = 280,
     VALUES = 281,
     DELETE = 282,
     FROM = 283,
     WHERE = 284,
     SELECT = 285,
     IS = 286,
     MINT = 287,
     VARCHAR = 288,
     AND = 289,
     DATE = 290,
     MFLOAT = 291,
     FOREIGN = 292,
     ERROR = 293,
     EQ = 294,
     NEQ = 295,
     LEQ = 296,
     GEQ = 297,
     LT = 298,
     GT = 299,
     LB = 300,
     RB = 301,
     FH = 302,
     DH = 303,
     DOT = 304,
     STAR = 305,
     QEXIT = 306
   };
#endif
/* Tokens.  */
#define VALUE_INT 258
#define VALUE_STRING 259
#define IDENTIFIER 260
#define OPERATOR 261
#define DATABASE 262
#define DATABASES 263
#define DROP 264
#define USE 265
#define INSERT 266
#define INTO 267
#define UPDATE 268
#define SET 269
#define DESC 270
#define REFERENCES 271
#define INDEX 272
#define TABLE 273
#define TABLES 274
#define SHOW 275
#define CREATE 276
#define PRIMARY 277
#define KEY 278
#define NOT 279
#define MYNULL 280
#define VALUES 281
#define DELETE 282
#define FROM 283
#define WHERE 284
#define SELECT 285
#define IS 286
#define MINT 287
#define VARCHAR 288
#define AND 289
#define DATE 290
#define MFLOAT 291
#define FOREIGN 292
#define ERROR 293
#define EQ 294
#define NEQ 295
#define LEQ 296
#define GEQ 297
#define LT 298
#define GT 299
#define LB 300
#define RB 301
#define FH 302
#define DH 303
#define DOT 304
#define STAR 305
#define QEXIT 306




/* Copy the first part of user declarations.  */
#line 1 "yacc.y"
  

/* 1. Statement */

#include "parser.h"

extern "C"
{
    void yyerror(const char *s);  
    extern int yylex(void);
}

int parserError;
ASType toplevel;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 225 "yacc.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   139

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNRULES -- Number of states.  */
#define YYNSTATES  136

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    12,    16,    20,    23,
      26,    33,    37,    40,    46,    52,    59,    66,    73,    80,
      82,    84,    88,    91,    96,   102,   113,   115,   117,   120,
     123,   125,   127,   131,   137,   139,   143,   145,   147,   149,
     151,   155,   159,   163,   167,   172,   174,   176,   178,   180,
     182,   184,   188,   190,   194,   196,   198,   200,   204,   206,
     210,   212,   216,   218
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      53,     0,    -1,    54,    -1,    -1,    54,    55,    -1,    20,
       8,    -1,    21,     7,     5,    -1,     9,     7,     5,    -1,
      10,     5,    -1,    20,    19,    -1,    21,    18,     5,    45,
      56,    46,    -1,     9,    18,     5,    -1,    15,     5,    -1,
      11,    12,     5,    26,    59,    -1,    27,    28,     5,    29,
      62,    -1,    13,     5,    14,    66,    29,    62,    -1,    30,
      67,    28,    70,    29,    62,    -1,    21,    17,     5,    45,
       5,    46,    -1,     9,    17,     5,    45,     5,    46,    -1,
      51,    -1,    57,    -1,    56,    48,    57,    -1,     5,    58,
      -1,     5,    58,    24,    25,    -1,    22,    23,    45,    71,
      46,    -1,    37,    23,    45,     5,    46,    16,     5,    45,
       5,    46,    -1,    32,    -1,    33,    -1,    32,     3,    -1,
      33,     3,    -1,    35,    -1,    36,    -1,    45,    60,    46,
      -1,    59,    48,    45,    60,    46,    -1,    61,    -1,    60,
      48,    61,    -1,     3,    -1,     4,    -1,    25,    -1,    63,
      -1,    62,    34,    63,    -1,    68,    64,    61,    -1,    68,
      64,    68,    -1,    68,    31,    25,    -1,    68,    31,    24,
      25,    -1,    39,    -1,    40,    -1,    41,    -1,    42,    -1,
      43,    -1,    44,    -1,     5,    39,    61,    -1,    65,    -1,
      66,    48,    65,    -1,    50,    -1,    69,    -1,     5,    -1,
       5,    49,     5,    -1,    68,    -1,    69,    48,    68,    -1,
       5,    -1,    70,    48,     5,    -1,     5,    -1,    71,    48,
       5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    59,    59,    66,    69,    76,    80,    85,    90,    95,
      99,   105,   110,   115,   121,   127,   134,   141,   147,   153,
     159,   164,   170,   176,   182,   188,   197,   201,   205,   210,
     215,   219,   225,   230,   237,   242,   249,   254,   259,   265,
     270,   277,   284,   291,   296,   303,   307,   311,   315,   319,
     323,   329,   336,   341,   348,   352,   358,   363,   371,   376,
     383,   388,   395,   400
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VALUE_INT", "VALUE_STRING",
  "IDENTIFIER", "OPERATOR", "DATABASE", "DATABASES", "DROP", "USE",
  "INSERT", "INTO", "UPDATE", "SET", "DESC", "REFERENCES", "INDEX",
  "TABLE", "TABLES", "SHOW", "CREATE", "PRIMARY", "KEY", "NOT", "MYNULL",
  "VALUES", "DELETE", "FROM", "WHERE", "SELECT", "IS", "MINT", "VARCHAR",
  "AND", "DATE", "MFLOAT", "FOREIGN", "ERROR", "EQ", "NEQ", "LEQ", "GEQ",
  "LT", "GT", "LB", "RB", "FH", "DH", "DOT", "STAR", "QEXIT", "$accept",
  "Program", "CommandList", "Stmt", "FieldList", "Field", "Type",
  "ValueLists", "ValueList", "Value", "WhereClause", "WhereSubClause",
  "Oper", "SetClause", "SetClauseList", "Selector", "Col", "ColList",
  "TableList", "ColumnList", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      56,    56,    57,    57,    57,    57,    58,    58,    58,    58,
      58,    58,    59,    59,    60,    60,    61,    61,    61,    62,
      62,    63,    63,    63,    63,    64,    64,    64,    64,    64,
      64,    65,    66,    66,    67,    67,    68,    68,    69,    69,
      70,    70,    71,    71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     3,     3,     2,     2,
       6,     3,     2,     5,     5,     6,     6,     6,     6,     1,
       1,     3,     2,     4,     5,    10,     1,     1,     2,     2,
       1,     1,     3,     5,     1,     3,     1,     1,     1,     1,
       3,     3,     3,     3,     4,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     1,     1,     3,     1,     3,
       1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     4,     0,     0,     0,     8,     0,
       0,    12,     5,     9,     0,     0,     0,     0,    56,    54,
       0,    58,    55,     7,     0,    11,     0,     0,     6,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    52,     0,
       0,     0,     0,    57,    60,     0,    59,     0,     0,    13,
       0,     0,     0,     0,     0,     0,     0,     0,    20,    14,
      39,     0,     0,     0,    18,    36,    37,    38,     0,    34,
       0,    51,    15,    53,    17,    26,    27,    30,    31,    22,
       0,     0,    10,     0,     0,     0,    45,    46,    47,    48,
      49,    50,     0,    16,    61,    32,     0,     0,    28,    29,
       0,     0,     0,    21,    40,     0,    43,    41,    42,    35,
       0,    23,    62,     0,     0,    44,    33,    24,     0,     0,
      63,     0,     0,     0,     0,    25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    14,    67,    68,    89,    59,    78,    79,
      69,    70,   102,    48,    49,    30,    71,    32,    55,   123
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -60
static const yytype_int8 yypact[] =
{
     -60,    36,    -5,   -60,    13,     9,    33,    52,    55,    16,
      20,    34,    -2,   -60,   -60,    60,    64,    65,   -60,    66,
      58,   -60,   -60,   -60,    68,    69,    70,    71,    28,   -60,
      50,   -60,    31,   -60,    35,   -60,    56,    76,   -60,    38,
      39,    57,    80,    82,    83,    84,    46,    53,   -60,   -22,
      88,    -3,    83,   -60,   -60,   -20,   -60,    48,    14,    47,
      14,    83,    76,    51,    23,    73,    75,   -25,   -60,    67,
     -60,    10,    83,    94,   -60,   -60,   -60,   -60,    -4,   -60,
      59,   -60,    67,   -60,   -60,    97,    99,   -60,   -60,    79,
      61,    62,   -60,    -3,    83,    43,   -60,   -60,   -60,   -60,
     -60,   -60,     8,    67,   -60,   -60,    14,    14,   -60,   -60,
      85,   100,   103,   -60,   -60,    86,   -60,   -60,   -60,   -60,
      15,   -60,   -60,    18,    63,   -60,   -60,   -60,   107,    98,
     -60,   108,    72,   110,    74,   -60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -60,   -60,   -60,   -60,   -60,    25,   -60,   -60,    12,   -59,
     -32,    22,   -60,    77,   -60,   -60,   -12,   -60,   -60,   -60
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      31,    81,    64,    28,     4,     5,     6,    61,     7,    72,
       8,    75,    76,    28,    18,     9,    10,    75,    76,    65,
      15,    92,    11,    93,    22,    12,    62,    24,    73,    82,
      16,    17,    56,    77,    66,    23,     3,    25,    26,    77,
     103,    95,   105,   117,   106,    19,    13,   119,    29,    96,
      97,    98,    99,   100,   101,    85,    86,    20,    87,    88,
      21,   126,    27,   106,   127,    33,   128,   115,   116,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    47,    46,    50,    51,    53,    52,    54,    28,    57,
     118,    58,    60,    63,    74,    80,    90,    84,    91,   104,
     108,    94,   109,   110,   107,   122,   111,   112,   124,   129,
     121,   125,   130,   132,   131,   134,   114,   133,   113,   120,
     135,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    83
};

static const yytype_int8 yycheck[] =
{
      12,    60,     5,     5,     9,    10,    11,    29,    13,    29,
      15,     3,     4,     5,     5,    20,    21,     3,     4,    22,
       7,    46,    27,    48,     8,    30,    48,     7,    48,    61,
      17,    18,    44,    25,    37,    19,     0,    17,    18,    25,
      72,    31,    46,   102,    48,    12,    51,   106,    50,    39,
      40,    41,    42,    43,    44,    32,    33,     5,    35,    36,
       5,    46,    28,    48,    46,     5,    48,    24,    25,     5,
       5,     5,    14,     5,     5,     5,     5,    49,    28,    48,
      45,     5,    26,    45,    45,     5,    29,     5,     5,     5,
     102,    45,    39,     5,    46,    48,    23,    46,    23,     5,
       3,    34,     3,    24,    45,     5,    45,    45,     5,    46,
      25,    25,     5,     5,    16,     5,    94,    45,    93,   107,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    53,    54,     0,     9,    10,    11,    13,    15,    20,
      21,    27,    30,    51,    55,     7,    17,    18,     5,    12,
       5,     5,     8,    19,     7,    17,    18,    28,     5,    50,
      67,    68,    69,     5,     5,     5,     5,    14,     5,     5,
       5,     5,    49,    28,    48,    45,    26,     5,    65,    66,
      45,    45,    29,     5,     5,    70,    68,     5,    45,    59,
      39,    29,    48,     5,     5,    22,    37,    56,    57,    62,
      63,    68,    29,    48,    46,     3,     4,    25,    60,    61,
      48,    61,    62,    65,    46,    32,    33,    35,    36,    58,
      23,    23,    46,    48,    34,    31,    39,    40,    41,    42,
      43,    44,    64,    62,     5,    46,    48,    45,     3,     3,
      24,    45,    45,    57,    63,    24,    25,    61,    68,    61,
      60,    25,     5,    71,     5,    25,    46,    46,    48,    46,
       5,    16,     5,    45,     5,    46
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

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
#line 60 "yacc.y"
    {
            toplevel.stmt_list = (yyvsp[(1) - (1)].stmt_list);
        ;}
    break;

  case 3:
#line 66 "yacc.y"
    {
            (yyval.stmt_list).clear();
        ;}
    break;

  case 4:
#line 70 "yacc.y"
    {
            (yyval.stmt_list) = (yyvsp[(1) - (2)].stmt_list);
            (yyval.stmt_list).push_back((yyvsp[(2) - (2)].stmt));
        ;}
    break;

  case 5:
#line 77 "yacc.y"
    {
            (yyval.stmt).id = SHOW_DB;
        ;}
    break;

  case 6:
#line 81 "yacc.y"
    {
            (yyval.stmt).id = CREATE_DB;
            (yyval.stmt).dbName = (yyvsp[(3) - (3)].ident);
        ;}
    break;

  case 7:
#line 86 "yacc.y"
    {
            (yyval.stmt).id = DROP_DB;
            (yyval.stmt).dbName = (yyvsp[(3) - (3)].ident);
        ;}
    break;

  case 8:
#line 91 "yacc.y"
    {
            (yyval.stmt).id = USE_DB;
            (yyval.stmt).dbName = (yyvsp[(2) - (2)].ident);
        ;}
    break;

  case 9:
#line 96 "yacc.y"
    {
            (yyval.stmt).id = SHOW_TABLE;
        ;}
    break;

  case 10:
#line 100 "yacc.y"
    {
            (yyval.stmt).id = CREATE_TABLE;
            (yyval.stmt).tbName = (yyvsp[(3) - (6)].ident);
            (yyval.stmt).field_list = (yyvsp[(5) - (6)].field_list);
        ;}
    break;

  case 11:
#line 106 "yacc.y"
    {
            (yyval.stmt).id = DROP_TABLE;
            (yyval.stmt).tbName = (yyvsp[(3) - (3)].ident);
        ;}
    break;

  case 12:
#line 111 "yacc.y"
    {
            (yyval.stmt).id = DESC_ST;
            (yyval.stmt).tbName = (yyvsp[(2) - (2)].ident);
        ;}
    break;

  case 13:
#line 116 "yacc.y"
    {
            (yyval.stmt).id = INSERT_ST;
            (yyval.stmt).tbName = (yyvsp[(3) - (5)].ident);
            (yyval.stmt).value_lists = (yyvsp[(5) - (5)].value_lists);
        ;}
    break;

  case 14:
#line 122 "yacc.y"
    {
            (yyval.stmt).id = DELETE_ST;
            (yyval.stmt).tbName = (yyvsp[(3) - (5)].ident);
            (yyval.stmt).where_list = (yyvsp[(5) - (5)].where_list);
        ;}
    break;

  case 15:
#line 128 "yacc.y"
    {
            (yyval.stmt).id = UPDATE_ST;
            (yyval.stmt).tbName = (yyvsp[(2) - (6)].ident);
            (yyval.stmt).setcl_list = (yyvsp[(4) - (6)].setcl_list);
            (yyval.stmt).where_list = (yyvsp[(6) - (6)].where_list);
        ;}
    break;

  case 16:
#line 135 "yacc.y"
    {
            (yyval.stmt).id = SELECT_ST;
            (yyval.stmt).sel = (yyvsp[(2) - (6)].sel);
            (yyval.stmt).table_list = (yyvsp[(4) - (6)].table_list);
            (yyval.stmt).where_list = (yyvsp[(6) - (6)].where_list);
        ;}
    break;

  case 17:
#line 142 "yacc.y"
    {
            (yyval.stmt).id = CREATE_IDX;
            (yyval.stmt).tbName = (yyvsp[(3) - (6)].ident);
            (yyval.stmt).colName = (yyvsp[(5) - (6)].ident);
        ;}
    break;

  case 18:
#line 148 "yacc.y"
    {
            (yyval.stmt).id = DROP_IDX;
            (yyval.stmt).tbName = (yyvsp[(3) - (6)].ident);
            (yyval.stmt).colName = (yyvsp[(5) - (6)].ident);
        ;}
    break;

  case 19:
#line 154 "yacc.y"
    {
            (yyval.stmt).id = EXIT_ST;
        ;}
    break;

  case 20:
#line 160 "yacc.y"
    {
            (yyval.field_list).clear();
            (yyval.field_list).push_back((yyvsp[(1) - (1)].field));
        ;}
    break;

  case 21:
#line 165 "yacc.y"
    {
            (yyval.field_list) = (yyvsp[(1) - (3)].field_list);
            (yyval.field_list).push_back((yyvsp[(3) - (3)].field));
        ;}
    break;

  case 22:
#line 171 "yacc.y"
    {
            (yyval.field).id = COL_FIELD;
            (yyval.field).colName = (yyvsp[(1) - (2)].ident);
            (yyval.field).type = (yyvsp[(2) - (2)].type);
        ;}
    break;

  case 23:
#line 177 "yacc.y"
    {
            (yyval.field).id = NOTNULL_COL_FIELD;
            (yyval.field).colName = (yyvsp[(1) - (4)].ident);
            (yyval.field).type = (yyvsp[(2) - (4)].type);
        ;}
    break;

  case 24:
#line 183 "yacc.y"
    {
            (yyval.field).id = PRIMARY_FIELD;
            (yyval.field).colList = (yyvsp[(4) - (5)].column_list);
            // TODO : Columnlist
        ;}
    break;

  case 25:
#line 189 "yacc.y"
    {
            (yyval.field).id = FOREIGN_FIELD;
            (yyval.field).colName = (yyvsp[(4) - (10)].ident);
            (yyval.field).tbName = (yyvsp[(7) - (10)].ident);
            (yyval.field).refcolName = (yyvsp[(9) - (10)].ident);
        ;}
    break;

  case 26:
#line 198 "yacc.y"
    {
            (yyval.type).id = INT_TYPE;
        ;}
    break;

  case 27:
#line 202 "yacc.y"
    {
            (yyval.type).id = VARCHAR_TYPE;
        ;}
    break;

  case 28:
#line 206 "yacc.y"
    {
            (yyval.type).id = INT_CONST_TYPE;
            (yyval.type).value_int = (yyvsp[(2) - (2)].value_int);
        ;}
    break;

  case 29:
#line 211 "yacc.y"
    {
            (yyval.type).id = VARCHAR_CONST_TYPE;
            (yyval.type).value_int = (yyvsp[(2) - (2)].value_int);
        ;}
    break;

  case 30:
#line 216 "yacc.y"
    {
            (yyval.type).id = DATE_TYPE;
        ;}
    break;

  case 31:
#line 220 "yacc.y"
    {
            (yyval.type).id = FLOAT_TYPE;
        ;}
    break;

  case 32:
#line 226 "yacc.y"
    {
            (yyval.value_lists).clear();
            (yyval.value_lists).push_back((yyvsp[(2) - (3)].value_list));            
        ;}
    break;

  case 33:
#line 231 "yacc.y"
    {
            (yyval.value_lists) = (yyvsp[(1) - (5)].value_lists);
            (yyval.value_lists).push_back((yyvsp[(4) - (5)].value_list));
        ;}
    break;

  case 34:
#line 238 "yacc.y"
    {
            (yyval.value_list).clear();
            (yyval.value_list).push_back((yyvsp[(1) - (1)].value));
        ;}
    break;

  case 35:
#line 243 "yacc.y"
    {
            (yyval.value_list) = (yyvsp[(1) - (3)].value_list);
            (yyval.value_list).push_back((yyvsp[(3) - (3)].value));
        ;}
    break;

  case 36:
#line 250 "yacc.y"
    {
            (yyval.value).id = VALUE_INT_ID;
            (yyval.value).value_int = (yyvsp[(1) - (1)].value_int);
        ;}
    break;

  case 37:
#line 255 "yacc.y"
    {
            (yyval.value).id = VALUE_STRING_ID;
            (yyval.value).value_string = (yyvsp[(1) - (1)].value_string);
        ;}
    break;

  case 38:
#line 260 "yacc.y"
    {
            (yyval.value).id = VALUE_NULL_ID;
        ;}
    break;

  case 39:
#line 266 "yacc.y"
    {
            (yyval.where_list).clear();
            (yyval.where_list).push_back((yyvsp[(1) - (1)].where));
        ;}
    break;

  case 40:
#line 271 "yacc.y"
    {
            (yyval.where_list) = (yyvsp[(1) - (3)].where_list);
            (yyval.where_list).push_back((yyvsp[(3) - (3)].where));
        ;}
    break;

  case 41:
#line 278 "yacc.y"
    {
            (yyval.where).id = COL_V_WHERECLAUSE;
            (yyval.where).fi = (yyvsp[(1) - (3)].col);
            (yyval.where).oper = (yyvsp[(2) - (3)].oper);
            (yyval.where).sval = (yyvsp[(3) - (3)].value);
        ;}
    break;

  case 42:
#line 285 "yacc.y"
    {
            (yyval.where).id = COL_C_WHERECLAUSE;
            (yyval.where).fi = (yyvsp[(1) - (3)].col);
            (yyval.where).oper = (yyvsp[(2) - (3)].oper);
            (yyval.where).scol = (yyvsp[(3) - (3)].col);
        ;}
    break;

  case 43:
#line 292 "yacc.y"
    {
            (yyval.where).id = COL_ISNULL_WHERECLAUSE;
            (yyval.where).fi = (yyvsp[(1) - (3)].col);
        ;}
    break;

  case 44:
#line 297 "yacc.y"
    {
            (yyval.where).id = COL_ISNOTNULL_WHERECLAUSE;
            (yyval.where).fi = (yyvsp[(1) - (4)].col);
        ;}
    break;

  case 45:
#line 304 "yacc.y"
    {
            (yyval.oper) = EQ_OPER;
        ;}
    break;

  case 46:
#line 308 "yacc.y"
    {
            (yyval.oper) = NEQ_OPER;
        ;}
    break;

  case 47:
#line 312 "yacc.y"
    {
            (yyval.oper) = LEQ_OPER;
        ;}
    break;

  case 48:
#line 316 "yacc.y"
    {
            (yyval.oper) = GEQ_OPER;
        ;}
    break;

  case 49:
#line 320 "yacc.y"
    {
            (yyval.oper) = LT_OPER;
        ;}
    break;

  case 50:
#line 324 "yacc.y"
    {
            (yyval.oper) = GT_OPER;
        ;}
    break;

  case 51:
#line 330 "yacc.y"
    {
            (yyval.setcl).colName = (yyvsp[(1) - (3)].ident);
            (yyval.setcl).value = (yyvsp[(3) - (3)].value);
        ;}
    break;

  case 52:
#line 337 "yacc.y"
    {
            (yyval.setcl_list).clear();
            (yyval.setcl_list).push_back((yyvsp[(1) - (1)].setcl));    
        ;}
    break;

  case 53:
#line 342 "yacc.y"
    {
            (yyval.setcl_list) = (yyvsp[(1) - (3)].setcl_list);
            (yyval.setcl_list).push_back((yyvsp[(3) - (3)].setcl));
        ;}
    break;

  case 54:
#line 349 "yacc.y"
    {
            (yyval.sel).col_list.clear();
        ;}
    break;

  case 55:
#line 353 "yacc.y"
    {
            (yyval.sel).col_list = (yyvsp[(1) - (1)].col_list);
        ;}
    break;

  case 56:
#line 359 "yacc.y"
    {
            (yyval.col).flag = 0;
            (yyval.col).colName = (yyvsp[(1) - (1)].ident);
        ;}
    break;

  case 57:
#line 364 "yacc.y"
    {
            (yyval.col).flag = 1;
            (yyval.col).tbName = (yyvsp[(1) - (3)].ident);
            (yyval.col).colName = (yyvsp[(3) - (3)].ident);
        ;}
    break;

  case 58:
#line 372 "yacc.y"
    {
            (yyval.col_list).clear();
            (yyval.col_list).push_back((yyvsp[(1) - (1)].col));            
        ;}
    break;

  case 59:
#line 377 "yacc.y"
    {
            (yyval.col_list) = (yyvsp[(1) - (3)].col_list);
            (yyval.col_list).push_back((yyvsp[(3) - (3)].col));
        ;}
    break;

  case 60:
#line 384 "yacc.y"
    {
            (yyval.table_list).clear();
            (yyval.table_list).push_back((yyvsp[(1) - (1)].ident));
        ;}
    break;

  case 61:
#line 389 "yacc.y"
    {
            (yyval.table_list) = (yyvsp[(1) - (3)].table_list);
            (yyval.table_list).push_back((yyvsp[(3) - (3)].ident));
        ;}
    break;

  case 62:
#line 396 "yacc.y"
    {
            (yyval.column_list).clear();
            (yyval.column_list).push_back((yyvsp[(1) - (1)].ident));
        ;}
    break;

  case 63:
#line 401 "yacc.y"
    {
            (yyval.column_list) = (yyvsp[(1) - (3)].column_list);
            (yyval.column_list).push_back((yyvsp[(3) - (3)].ident));
        ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2033 "yacc.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 407 "yacc.y"
  

void yyerror(const char *s)
{
    parserError = 1;
    //std::cerr << s << std::endl;
}  




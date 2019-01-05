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
     VALUE_FLOAT = 260,
     VALUE_DATE = 261,
     IDENTIFIER = 262,
     OPERATOR = 263,
     DATABASE = 264,
     DATABASES = 265,
     DROP = 266,
     USE = 267,
     INSERT = 268,
     INTO = 269,
     UPDATE = 270,
     SET = 271,
     DESC = 272,
     REFERENCES = 273,
     INDEX = 274,
     TABLE = 275,
     TABLES = 276,
     SHOW = 277,
     CREATE = 278,
     PRIMARY = 279,
     KEY = 280,
     NOT = 281,
     MYNULL = 282,
     VALUES = 283,
     DELETE = 284,
     FROM = 285,
     WHERE = 286,
     SELECT = 287,
     IS = 288,
     MINT = 289,
     VARCHAR = 290,
     AND = 291,
     DATE = 292,
     MFLOAT = 293,
     FOREIGN = 294,
     ERROR = 295,
     GLIKE = 296,
     EQ = 297,
     NEQ = 298,
     LEQ = 299,
     GEQ = 300,
     LT = 301,
     GT = 302,
     LB = 303,
     RB = 304,
     FH = 305,
     DH = 306,
     DOT = 307,
     STAR = 308,
     QEXIT = 309,
     QCLOSE = 310,
     QMIN = 311,
     QMAX = 312,
     QAVG = 313,
     QSUM = 314,
     QCHAR = 315,
     ORDERBY = 316,
     GROUPBY = 317,
     ASC = 318
   };
#endif
/* Tokens.  */
#define VALUE_INT 258
#define VALUE_STRING 259
#define VALUE_FLOAT 260
#define VALUE_DATE 261
#define IDENTIFIER 262
#define OPERATOR 263
#define DATABASE 264
#define DATABASES 265
#define DROP 266
#define USE 267
#define INSERT 268
#define INTO 269
#define UPDATE 270
#define SET 271
#define DESC 272
#define REFERENCES 273
#define INDEX 274
#define TABLE 275
#define TABLES 276
#define SHOW 277
#define CREATE 278
#define PRIMARY 279
#define KEY 280
#define NOT 281
#define MYNULL 282
#define VALUES 283
#define DELETE 284
#define FROM 285
#define WHERE 286
#define SELECT 287
#define IS 288
#define MINT 289
#define VARCHAR 290
#define AND 291
#define DATE 292
#define MFLOAT 293
#define FOREIGN 294
#define ERROR 295
#define GLIKE 296
#define EQ 297
#define NEQ 298
#define LEQ 299
#define GEQ 300
#define LT 301
#define GT 302
#define LB 303
#define RB 304
#define FH 305
#define DH 306
#define DOT 307
#define STAR 308
#define QEXIT 309
#define QCLOSE 310
#define QMIN 311
#define QMAX 312
#define QAVG 313
#define QSUM 314
#define QCHAR 315
#define ORDERBY 316
#define GROUPBY 317
#define ASC 318




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
#line 249 "yacc.tab.c"

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
#define YYLAST   206

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNRULES -- Number of states.  */
#define YYNSTATES  185

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    12,    16,    20,    23,
      26,    33,    37,    40,    46,    51,    57,    65,    72,    79,
      81,    83,    87,    89,    93,    96,   101,   107,   118,   120,
     122,   127,   132,   137,   139,   141,   145,   151,   153,   157,
     159,   161,   163,   165,   167,   170,   171,   173,   177,   181,
     185,   189,   194,   198,   203,   205,   207,   209,   211,   213,
     215,   219,   221,   225,   227,   229,   231,   235,   237,   242,
     247,   252,   257,   259,   263,   265,   269,   271,   275,   278,
     281,   283,   285,   289,   291,   295,   296,   299,   300
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      65,     0,    -1,    66,    -1,    -1,    66,    67,    -1,    22,
      10,    -1,    23,     9,     7,    -1,    11,     9,     7,    -1,
      12,     7,    -1,    22,    21,    -1,    23,    20,     7,    48,
      68,    49,    -1,    11,    20,     7,    -1,    17,     7,    -1,
      13,    14,     7,    28,    71,    -1,    29,    30,     7,    74,
      -1,    15,     7,    16,    79,    74,    -1,    32,    80,    30,
      87,    74,    90,    89,    -1,    23,    19,     7,    48,     7,
      49,    -1,    11,    19,     7,    48,     7,    49,    -1,    54,
      -1,    55,    -1,    22,    20,     7,    -1,    69,    -1,    68,
      51,    69,    -1,     7,    70,    -1,     7,    70,    26,    27,
      -1,    24,    25,    48,    88,    49,    -1,    39,    25,    48,
       7,    49,    18,     7,    48,     7,    49,    -1,    34,    -1,
      35,    -1,    34,    48,     3,    49,    -1,    35,    48,     3,
      49,    -1,    60,    48,     3,    49,    -1,    37,    -1,    38,
      -1,    48,    72,    49,    -1,    71,    51,    48,    72,    49,
      -1,    73,    -1,    72,    51,    73,    -1,     3,    -1,     4,
      -1,     5,    -1,     6,    -1,    27,    -1,    31,    75,    -1,
      -1,    76,    -1,    75,    36,    76,    -1,    81,    77,    73,
      -1,    81,    77,    81,    -1,    81,    33,    27,    -1,    81,
      33,    26,    27,    -1,    81,    41,     4,    -1,    81,    26,
      41,     4,    -1,    42,    -1,    43,    -1,    44,    -1,    45,
      -1,    46,    -1,    47,    -1,     7,    42,    73,    -1,    78,
      -1,    79,    51,    78,    -1,    53,    -1,    84,    -1,     7,
      -1,     7,    52,     7,    -1,    81,    -1,    59,    48,    81,
      49,    -1,    58,    48,    81,    49,    -1,    57,    48,    81,
      49,    -1,    56,    48,    81,    49,    -1,    81,    -1,    83,
      51,    81,    -1,    82,    -1,    84,    51,    82,    -1,    86,
      -1,    85,    51,    86,    -1,    82,    17,    -1,    82,    63,
      -1,    82,    -1,     7,    -1,    87,    51,     7,    -1,     7,
      -1,    88,    51,     7,    -1,    -1,    61,    85,    -1,    -1,
      62,    83,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    70,    70,    77,    80,    87,    91,    96,   101,   106,
     110,   116,   121,   126,   132,   138,   145,   154,   160,   166,
     170,   174,   181,   186,   192,   198,   204,   210,   219,   224,
     229,   234,   239,   244,   249,   256,   261,   268,   273,   280,
     285,   290,   295,   300,   306,   311,   315,   320,   327,   334,
     341,   346,   351,   357,   365,   369,   373,   377,   381,   385,
     391,   398,   403,   410,   414,   420,   426,   435,   440,   445,
     450,   455,   462,   467,   474,   479,   486,   491,   498,   503,
     508,   515,   520,   527,   532,   540,   543,   549,   552
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VALUE_INT", "VALUE_STRING",
  "VALUE_FLOAT", "VALUE_DATE", "IDENTIFIER", "OPERATOR", "DATABASE",
  "DATABASES", "DROP", "USE", "INSERT", "INTO", "UPDATE", "SET", "DESC",
  "REFERENCES", "INDEX", "TABLE", "TABLES", "SHOW", "CREATE", "PRIMARY",
  "KEY", "NOT", "MYNULL", "VALUES", "DELETE", "FROM", "WHERE", "SELECT",
  "IS", "MINT", "VARCHAR", "AND", "DATE", "MFLOAT", "FOREIGN", "ERROR",
  "GLIKE", "EQ", "NEQ", "LEQ", "GEQ", "LT", "GT", "LB", "RB", "FH", "DH",
  "DOT", "STAR", "QEXIT", "QCLOSE", "QMIN", "QMAX", "QAVG", "QSUM",
  "QCHAR", "ORDERBY", "GROUPBY", "ASC", "$accept", "Program",
  "CommandList", "Stmt", "FieldList", "Field", "Type", "ValueLists",
  "ValueList", "Value", "WhereClauseX", "WhereClause", "WhereSubClause",
  "Oper", "SetClause", "SetClauseList", "Selector", "Col", "ACol",
  "ColList", "AColList", "OColList", "OCol", "TableList", "ColumnList",
  "OrderByClause", "GroupByClause", 0
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    65,    66,    66,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    68,    68,    69,    69,    69,    69,    70,    70,
      70,    70,    70,    70,    70,    71,    71,    72,    72,    73,
      73,    73,    73,    73,    74,    74,    75,    75,    76,    76,
      76,    76,    76,    76,    77,    77,    77,    77,    77,    77,
      78,    79,    79,    80,    80,    81,    81,    82,    82,    82,
      82,    82,    83,    83,    84,    84,    85,    85,    86,    86,
      86,    87,    87,    88,    88,    89,    89,    90,    90
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     3,     3,     2,     2,
       6,     3,     2,     5,     4,     5,     7,     6,     6,     1,
       1,     3,     1,     3,     2,     4,     5,    10,     1,     1,
       4,     4,     4,     1,     1,     3,     5,     1,     3,     1,
       1,     1,     1,     1,     2,     0,     1,     3,     3,     3,
       3,     4,     3,     4,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     1,     1,     1,     3,     1,     4,     4,
       4,     4,     1,     3,     1,     3,     1,     3,     2,     2,
       1,     1,     3,     1,     3,     0,     2,     0,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,    20,     4,     0,     0,     0,     8,
       0,     0,    12,     5,     0,     9,     0,     0,     0,     0,
      65,    63,     0,     0,     0,     0,     0,    67,    74,    64,
       7,     0,    11,     0,     0,    21,     6,     0,     0,    45,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      61,    45,     0,     0,     0,    14,    66,     0,     0,     0,
       0,    81,    45,    75,     0,     0,    13,     0,     0,    15,
       0,     0,     0,     0,     0,    22,    44,    46,     0,    71,
      70,    69,    68,     0,    87,    18,    39,    40,    41,    42,
      43,     0,    37,     0,    60,    62,    17,    28,    29,    33,
      34,     0,    24,     0,     0,    10,     0,     0,     0,     0,
       0,    54,    55,    56,    57,    58,    59,     0,    82,     0,
      85,    35,     0,     0,     0,     0,     0,     0,     0,     0,
      23,    47,     0,     0,    50,    52,    48,    49,    72,    88,
       0,    16,    38,     0,     0,     0,     0,    25,    83,     0,
       0,    53,    51,     0,    80,    86,    76,    36,    30,    31,
      32,    26,     0,     0,    73,    78,    79,     0,    84,     0,
      77,     0,     0,     0,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    15,    84,    85,   112,    76,   101,   102,
      65,    86,    87,   127,    60,    61,    36,    37,   164,   149,
      39,   165,   166,    72,   159,   151,   130
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -74
static const yytype_int16 yypact[] =
{
     -74,     7,    10,   -74,    15,     9,    24,    12,    43,    16,
      70,    38,    -1,   -74,   -74,   -74,    84,    85,    90,   -74,
      92,    86,   -74,   -74,    93,   -74,    94,    96,    97,    98,
      55,   -74,    58,    60,    61,    62,    81,   -74,   -74,    63,
     -74,    65,   -74,    87,   109,   -74,   -74,    69,    71,    89,
     111,   114,   114,   114,   114,   115,     4,   116,    76,    83,
     -74,   -23,   119,     5,   114,   -74,   -74,    78,    79,    80,
      82,   -74,   -21,   -74,    88,    67,    91,    67,   109,   -74,
      95,   -20,   105,   107,    -8,   -74,    99,   -74,    41,   -74,
     -74,   -74,   -74,   126,    72,   -74,   -74,   -74,   -74,   -74,
     -74,    26,   -74,   100,   -74,   -74,   -74,   101,   102,   -74,
     -74,   103,   110,   104,   106,   -74,     5,   114,   112,    54,
     134,   -74,   -74,   -74,   -74,   -74,   -74,    42,   -74,   114,
     108,   -74,    67,    67,   136,   137,   138,   118,   139,   140,
     -74,   -74,   151,   129,   -74,   -74,   -74,   -74,   -74,   113,
       4,   -74,   -74,    44,   117,   121,   122,   -74,   -74,    47,
     123,   -74,   -74,   114,   -12,   124,   -74,   -74,   -74,   -74,
     -74,   -74,   150,   125,   -74,   -74,   -74,     4,   -74,   152,
     -74,   120,   153,   127,   -74
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -74,   -74,   -74,   -74,   -74,    45,   -74,   -74,    25,   -73,
     -41,   -74,    46,   -74,   128,   -74,   -74,   -51,    -3,   -74,
     -74,   -74,   -15,   -74,   -74,   -74,   -74
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      67,    68,    69,    70,   104,   175,    30,     3,    64,    38,
      64,    30,    81,    88,   107,   108,    19,   109,   110,    21,
      79,     4,     5,     6,    16,     7,    23,     8,    78,    82,
      93,    94,     9,    10,    17,    18,    24,    25,    20,    11,
     111,   115,    12,   116,    83,    96,    97,    98,    99,    30,
      22,   176,    31,    73,   146,    32,    33,    34,    35,   152,
      32,    33,    34,    35,    13,    14,    88,   118,    29,   100,
      96,    97,    98,    99,   119,   131,   147,   132,   148,    26,
     143,   144,   120,   121,   122,   123,   124,   125,   126,    27,
      28,    40,    41,   167,   100,   132,   171,    42,   172,    43,
      45,    46,    44,    47,    48,    49,    51,    50,    52,    53,
      54,    55,   174,    57,    56,    58,    59,    62,    66,    63,
      64,    30,    71,    74,    75,    77,    80,    89,    90,    91,
     113,    92,   114,   128,   129,   117,   137,    95,   145,   154,
     155,   156,   103,   179,   106,   157,   158,   160,   133,   134,
     135,   136,   138,   142,   139,   161,   162,   178,   153,   181,
     183,   140,   180,   141,   163,     0,   168,     0,   182,   150,
     169,   170,   173,     0,     0,   177,   184,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105
};

static const yytype_int16 yycheck[] =
{
      51,    52,    53,    54,    77,    17,     7,     0,    31,    12,
      31,     7,     7,    64,    34,    35,     7,    37,    38,     7,
      61,    11,    12,    13,     9,    15,    10,    17,    51,    24,
      51,    72,    22,    23,    19,    20,    20,    21,    14,    29,
      60,    49,    32,    51,    39,     3,     4,     5,     6,     7,
       7,    63,    53,    56,   127,    56,    57,    58,    59,   132,
      56,    57,    58,    59,    54,    55,   117,    26,    30,    27,
       3,     4,     5,     6,    33,    49,   127,    51,   129,     9,
      26,    27,    41,    42,    43,    44,    45,    46,    47,    19,
      20,     7,     7,    49,    27,    51,    49,     7,    51,     7,
       7,     7,    16,     7,     7,     7,    48,    52,    48,    48,
      48,    30,   163,    48,    51,    28,     7,    48,     7,    48,
      31,     7,     7,     7,    48,    42,     7,    49,    49,    49,
      25,    49,    25,     7,    62,    36,    26,    49,     4,     3,
       3,     3,    51,    18,    49,    27,     7,     7,    48,    48,
      48,    48,    48,    41,    48,     4,    27,     7,   133,     7,
       7,   116,   177,   117,    51,    -1,    49,    -1,    48,    61,
      49,    49,    49,    -1,    -1,    51,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    65,    66,     0,    11,    12,    13,    15,    17,    22,
      23,    29,    32,    54,    55,    67,     9,    19,    20,     7,
      14,     7,     7,    10,    20,    21,     9,    19,    20,    30,
       7,    53,    56,    57,    58,    59,    80,    81,    82,    84,
       7,     7,     7,     7,    16,     7,     7,     7,     7,     7,
      52,    48,    48,    48,    48,    30,    51,    48,    28,     7,
      78,    79,    48,    48,    31,    74,     7,    81,    81,    81,
      81,     7,    87,    82,     7,    48,    71,    42,    51,    74,
       7,     7,    24,    39,    68,    69,    75,    76,    81,    49,
      49,    49,    49,    51,    74,    49,     3,     4,     5,     6,
      27,    72,    73,    51,    73,    78,    49,    34,    35,    37,
      38,    60,    70,    25,    25,    49,    51,    36,    26,    33,
      41,    42,    43,    44,    45,    46,    47,    77,     7,    62,
      90,    49,    51,    48,    48,    48,    48,    26,    48,    48,
      69,    76,    41,    26,    27,     4,    73,    81,    81,    83,
      61,    89,    73,    72,     3,     3,     3,    27,     7,    88,
       7,     4,    27,    51,    82,    85,    86,    49,    49,    49,
      49,    49,    51,    49,    81,    17,    63,    51,     7,    18,
      86,     7,    48,     7,    49
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
#line 71 "yacc.y"
    {
            toplevel.stmt_list = (yyvsp[(1) - (1)].stmt_list);
        ;}
    break;

  case 3:
#line 77 "yacc.y"
    {
            (yyval.stmt_list).clear();
        ;}
    break;

  case 4:
#line 81 "yacc.y"
    {
            (yyval.stmt_list) = (yyvsp[(1) - (2)].stmt_list);
            (yyval.stmt_list).push_back((yyvsp[(2) - (2)].stmt));
        ;}
    break;

  case 5:
#line 88 "yacc.y"
    {
            (yyval.stmt).id = SHOW_DB;
        ;}
    break;

  case 6:
#line 92 "yacc.y"
    {
            (yyval.stmt).id = CREATE_DB;
            (yyval.stmt).dbName = (yyvsp[(3) - (3)].ident);
        ;}
    break;

  case 7:
#line 97 "yacc.y"
    {
            (yyval.stmt).id = DROP_DB;
            (yyval.stmt).dbName = (yyvsp[(3) - (3)].ident);
        ;}
    break;

  case 8:
#line 102 "yacc.y"
    {
            (yyval.stmt).id = USE_DB;
            (yyval.stmt).dbName = (yyvsp[(2) - (2)].ident);
        ;}
    break;

  case 9:
#line 107 "yacc.y"
    {
            (yyval.stmt).id = SHOW_TABLE;
        ;}
    break;

  case 10:
#line 111 "yacc.y"
    {
            (yyval.stmt).id = CREATE_TABLE;
            (yyval.stmt).tbName = (yyvsp[(3) - (6)].ident);
            (yyval.stmt).field_list = (yyvsp[(5) - (6)].field_list);
        ;}
    break;

  case 11:
#line 117 "yacc.y"
    {
            (yyval.stmt).id = DROP_TABLE;
            (yyval.stmt).tbName = (yyvsp[(3) - (3)].ident);
        ;}
    break;

  case 12:
#line 122 "yacc.y"
    {
            (yyval.stmt).id = DESC_ST;
            (yyval.stmt).tbName = (yyvsp[(2) - (2)].ident);
        ;}
    break;

  case 13:
#line 127 "yacc.y"
    {
            (yyval.stmt).id = INSERT_ST;
            (yyval.stmt).tbName = (yyvsp[(3) - (5)].ident);
            (yyval.stmt).value_lists = (yyvsp[(5) - (5)].value_lists);
        ;}
    break;

  case 14:
#line 133 "yacc.y"
    {
            (yyval.stmt).id = DELETE_ST;
            (yyval.stmt).tbName = (yyvsp[(3) - (4)].ident);
            (yyval.stmt).where_list = (yyvsp[(4) - (4)].where_list);
        ;}
    break;

  case 15:
#line 139 "yacc.y"
    {
            (yyval.stmt).id = UPDATE_ST;
            (yyval.stmt).tbName = (yyvsp[(2) - (5)].ident);
            (yyval.stmt).setcl_list = (yyvsp[(4) - (5)].setcl_list);
            (yyval.stmt).where_list = (yyvsp[(5) - (5)].where_list);
        ;}
    break;

  case 16:
#line 146 "yacc.y"
    {
            (yyval.stmt).id = SELECT_ST;
            (yyval.stmt).sel = (yyvsp[(2) - (7)].sel);
            (yyval.stmt).table_list = (yyvsp[(4) - (7)].table_list);
            (yyval.stmt).where_list = (yyvsp[(5) - (7)].where_list);
            (yyval.stmt).group_list = (yyvsp[(6) - (7)].col_list);
            (yyval.stmt).order_list = (yyvsp[(7) - (7)].col_list);
        ;}
    break;

  case 17:
#line 155 "yacc.y"
    {
            (yyval.stmt).id = CREATE_IDX;
            (yyval.stmt).tbName = (yyvsp[(3) - (6)].ident);
            (yyval.stmt).colName = (yyvsp[(5) - (6)].ident);
        ;}
    break;

  case 18:
#line 161 "yacc.y"
    {
            (yyval.stmt).id = DROP_IDX;
            (yyval.stmt).tbName = (yyvsp[(3) - (6)].ident);
            (yyval.stmt).colName = (yyvsp[(5) - (6)].ident);
        ;}
    break;

  case 19:
#line 167 "yacc.y"
    {
            (yyval.stmt).id = EXIT_ST;
        ;}
    break;

  case 20:
#line 171 "yacc.y"
    {
            (yyval.stmt).id = CLOSE_ST;
        ;}
    break;

  case 21:
#line 175 "yacc.y"
    {
            (yyval.stmt).id = SHOW_TABLE_ID;
            (yyval.stmt).tbName = (yyvsp[(3) - (3)].ident);
        ;}
    break;

  case 22:
#line 182 "yacc.y"
    {
            (yyval.field_list).clear();
            (yyval.field_list).push_back((yyvsp[(1) - (1)].field));
        ;}
    break;

  case 23:
#line 187 "yacc.y"
    {
            (yyval.field_list) = (yyvsp[(1) - (3)].field_list);
            (yyval.field_list).push_back((yyvsp[(3) - (3)].field));
        ;}
    break;

  case 24:
#line 193 "yacc.y"
    {
            (yyval.field).id = COL_FIELD;
            (yyval.field).colName = (yyvsp[(1) - (2)].ident);
            (yyval.field).type = (yyvsp[(2) - (2)].type);
        ;}
    break;

  case 25:
#line 199 "yacc.y"
    {
            (yyval.field).id = NOTNULL_COL_FIELD;
            (yyval.field).colName = (yyvsp[(1) - (4)].ident);
            (yyval.field).type = (yyvsp[(2) - (4)].type);
        ;}
    break;

  case 26:
#line 205 "yacc.y"
    {
            (yyval.field).id = PRIMARY_FIELD;
            (yyval.field).colList = (yyvsp[(4) - (5)].column_list);
            // TODO : Columnlist
        ;}
    break;

  case 27:
#line 211 "yacc.y"
    {
            (yyval.field).id = FOREIGN_FIELD;
            (yyval.field).colName = (yyvsp[(4) - (10)].ident);
            (yyval.field).tbName = (yyvsp[(7) - (10)].ident);
            (yyval.field).refcolName = (yyvsp[(9) - (10)].ident);
        ;}
    break;

  case 28:
#line 220 "yacc.y"
    {
            (yyval.type).id = INT_TYPE;
            (yyval.type).length = 4;
        ;}
    break;

  case 29:
#line 225 "yacc.y"
    {
            (yyval.type).id = VARCHAR_TYPE;
            (yyval.type).length = MAXNAME + 1;
        ;}
    break;

  case 30:
#line 230 "yacc.y"
    {
            (yyval.type).id = INT_TYPE;
            (yyval.type).length = 4;
        ;}
    break;

  case 31:
#line 235 "yacc.y"
    {
            (yyval.type).id = VARCHAR_TYPE;
            (yyval.type).length = (yyvsp[(3) - (4)].value_int) + 3;
        ;}
    break;

  case 32:
#line 240 "yacc.y"
    {
            (yyval.type).id = VARCHAR_TYPE;
            (yyval.type).length = (yyvsp[(3) - (4)].value_int) + 3;
        ;}
    break;

  case 33:
#line 245 "yacc.y"
    {
            (yyval.type).id = DATE_TYPE;
            (yyval.type).length = 4;
        ;}
    break;

  case 34:
#line 250 "yacc.y"
    {
            (yyval.type).id = FLOAT_TYPE;
            (yyval.type).length = 4;
        ;}
    break;

  case 35:
#line 257 "yacc.y"
    {
            (yyval.value_lists).clear();
            (yyval.value_lists).push_back((yyvsp[(2) - (3)].value_list));            
        ;}
    break;

  case 36:
#line 262 "yacc.y"
    {
            (yyval.value_lists) = (yyvsp[(1) - (5)].value_lists);
            (yyval.value_lists).push_back((yyvsp[(4) - (5)].value_list));
        ;}
    break;

  case 37:
#line 269 "yacc.y"
    {
            (yyval.value_list).clear();
            (yyval.value_list).push_back((yyvsp[(1) - (1)].value));
        ;}
    break;

  case 38:
#line 274 "yacc.y"
    {
            (yyval.value_list) = (yyvsp[(1) - (3)].value_list);
            (yyval.value_list).push_back((yyvsp[(3) - (3)].value));
        ;}
    break;

  case 39:
#line 281 "yacc.y"
    {
            (yyval.value).id = VALUE_INT_ID;
            (yyval.value).value_int = (yyvsp[(1) - (1)].value_int);
        ;}
    break;

  case 40:
#line 286 "yacc.y"
    {
            (yyval.value).id = VALUE_STRING_ID;
            (yyval.value).value_string = (yyvsp[(1) - (1)].value_string);
        ;}
    break;

  case 41:
#line 291 "yacc.y"
    {
            (yyval.value).id = VALUE_FLOAT_ID;
            (yyval.value).value_float = (yyvsp[(1) - (1)].value_float);
        ;}
    break;

  case 42:
#line 296 "yacc.y"
    {
            (yyval.value).id = VALUE_DATE_ID;
            (yyval.value).value_string = (yyvsp[(1) - (1)].value_string);
        ;}
    break;

  case 43:
#line 301 "yacc.y"
    {
            (yyval.value).id = VALUE_NULL_ID;
        ;}
    break;

  case 44:
#line 307 "yacc.y"
    {
            (yyval.where_list) = (yyvsp[(2) - (2)].where_list);
        ;}
    break;

  case 45:
#line 311 "yacc.y"
    {
            (yyval.where_list).clear();
        ;}
    break;

  case 46:
#line 316 "yacc.y"
    {
            (yyval.where_list).clear();
            (yyval.where_list).push_back((yyvsp[(1) - (1)].where));
        ;}
    break;

  case 47:
#line 321 "yacc.y"
    {
            (yyval.where_list) = (yyvsp[(1) - (3)].where_list);
            (yyval.where_list).push_back((yyvsp[(3) - (3)].where));
        ;}
    break;

  case 48:
#line 328 "yacc.y"
    {
            (yyval.where).id = COL_V_WHERECLAUSE;
            (yyval.where).fi = (yyvsp[(1) - (3)].col);
            (yyval.where).oper = (yyvsp[(2) - (3)].oper);
            (yyval.where).sval = (yyvsp[(3) - (3)].value);
        ;}
    break;

  case 49:
#line 335 "yacc.y"
    {
            (yyval.where).id = COL_C_WHERECLAUSE;
            (yyval.where).fi = (yyvsp[(1) - (3)].col);
            (yyval.where).oper = (yyvsp[(2) - (3)].oper);
            (yyval.where).scol = (yyvsp[(3) - (3)].col);
        ;}
    break;

  case 50:
#line 342 "yacc.y"
    {
            (yyval.where).id = COL_ISNULL_WHERECLAUSE;
            (yyval.where).fi = (yyvsp[(1) - (3)].col);
        ;}
    break;

  case 51:
#line 347 "yacc.y"
    {
            (yyval.where).id = COL_ISNOTNULL_WHERECLAUSE;
            (yyval.where).fi = (yyvsp[(1) - (4)].col);
        ;}
    break;

  case 52:
#line 352 "yacc.y"
    {
            (yyval.where).id = COL_LIKECLAUSE;
            (yyval.where).fi = (yyvsp[(1) - (3)].col);
            (yyval.where).pattern = (yyvsp[(3) - (3)].value_string);
        ;}
    break;

  case 53:
#line 358 "yacc.y"
    {
            (yyval.where).id = COL_NOTLIKECLAUSE;
            (yyval.where).fi = (yyvsp[(1) - (4)].col);
            (yyval.where).pattern = (yyvsp[(4) - (4)].value_string);
        ;}
    break;

  case 54:
#line 366 "yacc.y"
    {
            (yyval.oper) = EQ_OPER;
        ;}
    break;

  case 55:
#line 370 "yacc.y"
    {
            (yyval.oper) = NEQ_OPER;
        ;}
    break;

  case 56:
#line 374 "yacc.y"
    {
            (yyval.oper) = LEQ_OPER;
        ;}
    break;

  case 57:
#line 378 "yacc.y"
    {
            (yyval.oper) = GEQ_OPER;
        ;}
    break;

  case 58:
#line 382 "yacc.y"
    {
            (yyval.oper) = LT_OPER;
        ;}
    break;

  case 59:
#line 386 "yacc.y"
    {
            (yyval.oper) = GT_OPER;
        ;}
    break;

  case 60:
#line 392 "yacc.y"
    {
            (yyval.setcl).colName = (yyvsp[(1) - (3)].ident);
            (yyval.setcl).value = (yyvsp[(3) - (3)].value);
        ;}
    break;

  case 61:
#line 399 "yacc.y"
    {
            (yyval.setcl_list).clear();
            (yyval.setcl_list).push_back((yyvsp[(1) - (1)].setcl));    
        ;}
    break;

  case 62:
#line 404 "yacc.y"
    {
            (yyval.setcl_list) = (yyvsp[(1) - (3)].setcl_list);
            (yyval.setcl_list).push_back((yyvsp[(3) - (3)].setcl));
        ;}
    break;

  case 63:
#line 411 "yacc.y"
    {
            (yyval.sel).col_list.clear();
        ;}
    break;

  case 64:
#line 415 "yacc.y"
    {
            (yyval.sel).col_list = (yyvsp[(1) - (1)].col_list);
        ;}
    break;

  case 65:
#line 421 "yacc.y"
    {
            (yyval.col).flag = 0;
            (yyval.col).aggtype = 0;
            (yyval.col).colName = (yyvsp[(1) - (1)].ident);
        ;}
    break;

  case 66:
#line 427 "yacc.y"
    {
            (yyval.col).flag = 1;
            (yyval.col).aggtype = 0;
            (yyval.col).tbName = (yyvsp[(1) - (3)].ident);
            (yyval.col).colName = (yyvsp[(3) - (3)].ident);
        ;}
    break;

  case 67:
#line 436 "yacc.y"
    {
            (yyval.col) = (yyvsp[(1) - (1)].col);
            (yyval.col).aggtype = 0;
        ;}
    break;

  case 68:
#line 441 "yacc.y"
    {
            (yyval.col) = (yyvsp[(3) - (4)].col);
            (yyval.col).aggtype = AGG_SUM;
        ;}
    break;

  case 69:
#line 446 "yacc.y"
    {
            (yyval.col) = (yyvsp[(3) - (4)].col);
            (yyval.col).aggtype = AGG_AVG;
        ;}
    break;

  case 70:
#line 451 "yacc.y"
    {
            (yyval.col) = (yyvsp[(3) - (4)].col);
            (yyval.col).aggtype = AGG_MAX;
        ;}
    break;

  case 71:
#line 456 "yacc.y"
    {
            (yyval.col) = (yyvsp[(3) - (4)].col);
            (yyval.col).aggtype = AGG_MIN;
        ;}
    break;

  case 72:
#line 463 "yacc.y"
    {
            (yyval.col_list).clear();
            (yyval.col_list).push_back((yyvsp[(1) - (1)].col));
        ;}
    break;

  case 73:
#line 468 "yacc.y"
    {
            (yyval.col_list) = (yyvsp[(1) - (3)].col_list);
            (yyval.col_list).push_back((yyvsp[(3) - (3)].col));
        ;}
    break;

  case 74:
#line 475 "yacc.y"
    {
            (yyval.col_list).clear();
            (yyval.col_list).push_back((yyvsp[(1) - (1)].col));            
        ;}
    break;

  case 75:
#line 480 "yacc.y"
    {
            (yyval.col_list) = (yyvsp[(1) - (3)].col_list);
            (yyval.col_list).push_back((yyvsp[(3) - (3)].col));
        ;}
    break;

  case 76:
#line 487 "yacc.y"
    {
            (yyval.col_list).clear();
            (yyval.col_list).push_back((yyvsp[(1) - (1)].col));
        ;}
    break;

  case 77:
#line 492 "yacc.y"
    {
            (yyval.col_list) = (yyvsp[(1) - (3)].col_list);
            (yyval.col_list).push_back((yyvsp[(3) - (3)].col));
        ;}
    break;

  case 78:
#line 499 "yacc.y"
    {
            (yyval.col) = (yyvsp[(1) - (2)].col);
            (yyval.col).ordtype = ORDER_BY_DEC;
        ;}
    break;

  case 79:
#line 504 "yacc.y"
    {
            (yyval.col) = (yyvsp[(1) - (2)].col);
            (yyval.col).ordtype = ORDER_BY_INC;
        ;}
    break;

  case 80:
#line 509 "yacc.y"
    {
            (yyval.col) = (yyvsp[(1) - (1)].col);
            (yyval.col).ordtype = ORDER_BY_INC;
        ;}
    break;

  case 81:
#line 516 "yacc.y"
    {
            (yyval.table_list).clear();
            (yyval.table_list).push_back((yyvsp[(1) - (1)].ident));
        ;}
    break;

  case 82:
#line 521 "yacc.y"
    {
            (yyval.table_list) = (yyvsp[(1) - (3)].table_list);
            (yyval.table_list).push_back((yyvsp[(3) - (3)].ident));
        ;}
    break;

  case 83:
#line 528 "yacc.y"
    {
            (yyval.column_list).clear();
            (yyval.column_list).push_back((yyvsp[(1) - (1)].ident));
        ;}
    break;

  case 84:
#line 533 "yacc.y"
    {
            (yyval.column_list) = (yyvsp[(1) - (3)].column_list);
            (yyval.column_list).push_back((yyvsp[(3) - (3)].ident));
        ;}
    break;

  case 85:
#line 540 "yacc.y"
    {
            (yyval.col_list).clear();
        ;}
    break;

  case 86:
#line 544 "yacc.y"
    {
            (yyval.col_list) = (yyvsp[(2) - (2)].col_list);
        ;}
    break;

  case 87:
#line 549 "yacc.y"
    {
            (yyval.col_list).clear();
        ;}
    break;

  case 88:
#line 553 "yacc.y"
    {
            (yyval.col_list) = (yyvsp[(2) - (2)].col_list);
        ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2312 "yacc.tab.c"
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


#line 557 "yacc.y"
  

void yyerror(const char *s)
{
    parserError = 1;
    //std::cerr << s << std::endl;
}  




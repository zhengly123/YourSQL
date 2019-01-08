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
#line 1 "yacc.y" /* yacc.c:339  */


/* 1. Statement */

#include "parser.h"

extern "C"
{
void yyerror(const char *s);
extern int yylex(void);
}

int parserError;
ASType toplevel;


#line 83 "yacc.tab.c" /* yacc.c:339  */

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
   by #include "yacc.tab.h".  */
#ifndef YY_YY_YACC_TAB_H_INCLUDED
# define YY_YY_YACC_TAB_H_INCLUDED
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
    QOUTPUT = 311,
    QMIN = 312,
    QMAX = 313,
    QAVG = 314,
    QSUM = 315,
    QCHAR = 316,
    ORDERBY = 317,
    GROUPBY = 318,
    ASC = 319
};
#endif

/* Value type.  */


extern YYSTYPE yylval;

int yyparse(void);

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 194 "yacc.tab.c" /* yacc.c:358  */

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
#  if (defined __cplusplus && !defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
 && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if !defined malloc && !defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if !defined free && !defined EXIT_SUCCESS
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   200

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  188

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
     0,    71,    71,    78,    81,    88,    92,    97,   102,   107,
   111,   117,   122,   127,   133,   139,   146,   156,   162,   168,
   172,   176,   183,   188,   194,   200,   206,   212,   221,   226,
   231,   236,   241,   246,   251,   258,   263,   270,   275,   282,
   287,   292,   297,   302,   308,   313,   317,   322,   329,   336,
   343,   348,   353,   359,   367,   371,   375,   379,   383,   387,
   393,   400,   405,   412,   416,   422,   428,   437,   442,   447,
   452,   457,   464,   469,   476,   481,   488,   493,   500,   505,
   510,   517,   522,   529,   534,   542,   545,   551,   554,   560,
   563
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "DOT", "STAR", "QEXIT", "QCLOSE", "QOUTPUT", "QMIN", "QMAX", "QAVG",
  "QSUM", "QCHAR", "ORDERBY", "GROUPBY", "ASC", "$accept", "Program",
  "CommandList", "Stmt", "FieldList", "Field", "Type", "ValueLists",
  "ValueList", "Value", "WhereClauseX", "WhereClause", "WhereSubClause",
  "Oper", "SetClause", "SetClauseList", "Selector", "Col", "ACol",
  "ColList", "AColList", "OColList", "OCol", "TableList", "ColumnList",
  "OrderByClause", "GroupByClause", "OutputClause", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319
};
# endif

#define YYPACT_NINF -74

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-74)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -74,     7,    10,   -74,    15,    30,    35,    70,    84,    59,
      62,    64,    -2,   -74,   -74,   -74,    89,    90,    91,   -74,
      92,    85,   -74,   -74,    93,   -74,    95,    96,    97,    98,
      54,   -74,    60,    61,    63,    65,    77,   -74,   -74,    66,
     -74,    67,   -74,    82,   107,   -74,   -74,    68,    71,    87,
     113,   114,   114,   114,   114,   115,     3,   116,    76,    83,
     -74,    -3,   119,     2,   114,   -74,   -74,    78,    79,    80,
      81,   -74,    -1,   -74,    86,    40,    88,    40,   107,   -74,
      94,   -23,   106,   108,   -20,   -74,   100,   -74,    42,   -74,
     -74,   -74,   -74,   125,    74,   -74,   -74,   -74,   -74,   -74,
     -74,    21,   -74,    99,   -74,   -74,   -74,   101,   102,   -74,
     -74,   103,   112,   104,   105,   -74,     2,   114,   117,    47,
     130,   -74,   -74,   -74,   -74,   -74,   -74,    13,   -74,   114,
     109,   -74,    40,    40,   137,   138,   139,   118,   141,   147,
     -74,   -74,   140,   128,   -74,   -74,   -74,   -74,   -74,   110,
       3,   111,   -74,    41,   120,   121,   123,   -74,   -74,    44,
     124,   -74,   -74,   114,   -11,   126,   -74,   142,   -74,   -74,
     -74,   -74,   -74,   -74,   149,   144,   -74,   -74,   -74,     3,
     -74,   -74,   150,   -74,   127,   152,   129,   -74
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
        {
                3, 0, 2, 1, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 19, 20, 4, 0, 0, 0, 8,
                0, 0, 12, 5, 0, 9, 0, 0, 0, 0,
                65, 63, 0, 0, 0, 0, 0, 67, 74, 64,
                7, 0, 11, 0, 0, 21, 6, 0, 0, 45,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                61, 45, 0, 0, 0, 14, 66, 0, 0, 0,
                0, 81, 45, 75, 0, 0, 13, 0, 0, 15,
                0, 0, 0, 0, 0, 22, 44, 46, 0, 71,
                70, 69, 68, 0, 87, 18, 39, 40, 41, 42,
                43, 0, 37, 0, 60, 62, 17, 28, 29, 33,
                34, 0, 24, 0, 0, 10, 0, 0, 0, 0,
                0, 54, 55, 56, 57, 58, 59, 0, 82, 0,
                85, 35, 0, 0, 0, 0, 0, 0, 0, 0,
                23, 47, 0, 0, 50, 52, 48, 49, 72, 88,
                0, 89, 38, 0, 0, 0, 0, 25, 83, 0,
                0, 53, 51, 0, 80, 86, 76, 0, 16, 36,
                30, 31, 32, 26, 0, 0, 73, 78, 79, 0,
                90, 84, 0, 77, 0, 0, 0, 27
        };

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -74,   -74,   -74,   -74,   -74,    48,   -74,   -74,    27,   -73,
     -25,   -74,    46,   -74,   122,   -74,   -74,   -51,    -4,   -74,
     -74,   -74,   -14,   -74,   -74,   -74,   -74,   -74
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
        {
                -1, 1, 2, 15, 84, 85, 112, 76, 101, 102,
                65, 86, 87, 127, 60, 61, 36, 37, 164, 149,
                39, 165, 166, 72, 159, 151, 130, 168
        };

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      67,    68,    69,    70,   104,    30,   177,     3,    38,    81,
      30,   107,   108,    88,   109,   110,    96,    97,    98,    99,
      30,     4,     5,     6,    16,     7,    82,     8,    64,   115,
      64,   116,     9,    10,    17,    18,    79,    19,   111,    11,
     100,    83,    12,    96,    97,    98,    99,    94,    78,    20,
      93,    31,    73,   178,   146,    32,    33,    34,    35,   152,
      32,    33,    34,    35,    13,    14,    88,   100,   118,    23,
     131,    26,   132,   143,   144,   119,   147,    21,   148,    24,
      25,    27,    28,   120,   121,   122,   123,   124,   125,   126,
     169,    22,   132,   173,    29,   174,    40,    41,    42,    43,
      45,    44,    46,    47,    48,    49,    50,    55,    51,    52,
      58,    53,   176,    54,    59,    57,    62,    56,    64,    63,
      66,    30,    71,    74,    75,    77,    80,    89,    90,    91,
      92,   113,   128,   114,   145,    95,   117,   129,   137,   103,
     154,   155,   156,   106,   161,   157,   180,   133,   158,   134,
     135,   136,   138,   139,   160,   162,   181,   184,   142,   186,
     153,   163,   182,   141,   140,   183,     0,   167,     0,   170,
     171,   150,   172,   175,     0,   185,     0,   179,   187,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105
};

static const yytype_int16 yycheck[] =
{
      51,    52,    53,    54,    77,     7,    17,     0,    12,     7,
       7,    34,    35,    64,    37,    38,     3,     4,     5,     6,
       7,    11,    12,    13,     9,    15,    24,    17,    31,    49,
      31,    51,    22,    23,    19,    20,    61,     7,    61,    29,
      27,    39,    32,     3,     4,     5,     6,    72,    51,    14,
      51,    53,    56,    64,   127,    57,    58,    59,    60,   132,
      57,    58,    59,    60,    54,    55,   117,    27,    26,    10,
      49,     9,    51,    26,    27,    33,   127,     7,   129,    20,
      21,    19,    20,    41,    42,    43,    44,    45,    46,    47,
      49,     7,    51,    49,    30,    51,     7,     7,     7,     7,
       7,    16,     7,     7,     7,     7,    52,    30,    48,    48,
      28,    48,   163,    48,     7,    48,    48,    51,    31,    48,
       7,     7,     7,     7,    48,    42,     7,    49,    49,    49,
      49,    25,     7,    25,     4,    49,    36,    63,    26,    51,
       3,     3,     3,    49,     4,    27,     4,    48,     7,    48,
      48,    48,    48,    48,     7,    27,     7,     7,    41,     7,
     133,    51,    18,   117,   116,   179,    -1,    56,    -1,    49,
      49,    62,    49,    49,    -1,    48,    -1,    51,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    66,    67,     0,    11,    12,    13,    15,    17,    22,
      23,    29,    32,    54,    55,    68,     9,    19,    20,     7,
      14,     7,     7,    10,    20,    21,     9,    19,    20,    30,
       7,    53,    57,    58,    59,    60,    81,    82,    83,    85,
       7,     7,     7,     7,    16,     7,     7,     7,     7,     7,
      52,    48,    48,    48,    48,    30,    51,    48,    28,     7,
      79,    80,    48,    48,    31,    75,     7,    82,    82,    82,
      82,     7,    88,    83,     7,    48,    72,    42,    51,    75,
       7,     7,    24,    39,    69,    70,    76,    77,    82,    49,
      49,    49,    49,    51,    75,    49,     3,     4,     5,     6,
      27,    73,    74,    51,    74,    79,    49,    34,    35,    37,
      38,    61,    71,    25,    25,    49,    51,    36,    26,    33,
      41,    42,    43,    44,    45,    46,    47,    78,     7,    63,
      91,    49,    51,    48,    48,    48,    48,    26,    48,    48,
      70,    77,    41,    26,    27,     4,    74,    82,    82,    84,
      62,    90,    74,    73,     3,     3,     3,    27,     7,    89,
       7,     4,    27,    51,    83,    86,    87,    56,    92,    49,
      49,    49,    49,    49,    51,    49,    82,    17,    64,    51,
       4,     7,    18,    87,     7,    48,     7,    49
};

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
        {
                0, 65, 66, 67, 67, 68, 68, 68, 68, 68,
                68, 68, 68, 68, 68, 68, 68, 68, 68, 68,
                68, 68, 69, 69, 70, 70, 70, 70, 71, 71,
                71, 71, 71, 71, 71, 72, 72, 73, 73, 74,
                74, 74, 74, 74, 75, 75, 76, 76, 77, 77,
                77, 77, 77, 77, 78, 78, 78, 78, 78, 78,
                79, 80, 80, 81, 81, 82, 82, 83, 83, 83,
                83, 83, 84, 84, 85, 85, 86, 86, 87, 87,
                87, 88, 88, 89, 89, 90, 90, 91, 91, 92,
                92
        };

/* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
        {
                0, 2, 1, 0, 2, 2, 3, 3, 2, 2,
                6, 3, 2, 5, 4, 5, 8, 6, 6, 1,
                1, 3, 1, 3, 2, 4, 5, 10, 1, 1,
                4, 4, 4, 1, 1, 3, 5, 1, 3, 1,
                1, 1, 1, 1, 2, 0, 1, 3, 3, 3,
                3, 4, 3, 4, 1, 1, 1, 1, 1, 1,
                3, 1, 3, 1, 1, 1, 3, 1, 4, 4,
                4, 4, 1, 3, 1, 3, 1, 3, 2, 2,
                1, 1, 3, 1, 3, 0, 2, 0, 2, 0,
                2
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
        yychar = yylex();
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
#line 72 "yacc.y" /* yacc.c:1646  */
    {
        toplevel.stmt_list = (yyvsp[0].stmt_list);
    }
#line 1410 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 78 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt_list).clear();
    }
#line 1418 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 82 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.stmt_list) = (yyvsp[-1].stmt_list);
        (yyval.stmt_list).push_back((yyvsp[0].stmt));
    }
#line 1427 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 89 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = SHOW_DB;
    }
#line 1435 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 93 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = CREATE_DB;
        (yyval.stmt).dbName = (yyvsp[0].ident);
    }
#line 1444 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 98 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = DROP_DB;
        (yyval.stmt).dbName = (yyvsp[0].ident);
    }
#line 1453 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 103 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = USE_DB;
        (yyval.stmt).dbName = (yyvsp[0].ident);
    }
#line 1462 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 108 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = SHOW_TABLE;
    }
#line 1470 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 112 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = CREATE_TABLE;
        (yyval.stmt).tbName = (yyvsp[-3].ident);
        (yyval.stmt).field_list = (yyvsp[-1].field_list);
    }
#line 1480 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 118 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = DROP_TABLE;
        (yyval.stmt).tbName = (yyvsp[0].ident);
    }
#line 1489 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 123 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = DESC_ST;
        (yyval.stmt).tbName = (yyvsp[0].ident);
    }
#line 1498 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 128 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = INSERT_ST;
        (yyval.stmt).tbName = (yyvsp[-2].ident);
        (yyval.stmt).value_lists = (yyvsp[0].value_lists);
    }
#line 1508 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 134 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = DELETE_ST;
        (yyval.stmt).tbName = (yyvsp[-1].ident);
        (yyval.stmt).where_list = (yyvsp[0].where_list);
    }
#line 1518 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 140 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = UPDATE_ST;
        (yyval.stmt).tbName = (yyvsp[-3].ident);
        (yyval.stmt).setcl_list = (yyvsp[-1].setcl_list);
        (yyval.stmt).where_list = (yyvsp[0].where_list);
    }
#line 1529 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 147 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = SELECT_ST;
        (yyval.stmt).sel = (yyvsp[-6].sel);
        (yyval.stmt).table_list = (yyvsp[-4].table_list);
        (yyval.stmt).where_list = (yyvsp[-3].where_list);
        (yyval.stmt).group_list = (yyvsp[-2].col_list);
        (yyval.stmt).order_list = (yyvsp[-1].col_list);
        (yyval.stmt).fileout = (yyvsp[0].fileout);
    }
#line 1543 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 157 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = CREATE_IDX;
        (yyval.stmt).tbName = (yyvsp[-3].ident);
        (yyval.stmt).colName = (yyvsp[-1].ident);
    }
#line 1553 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 163 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = DROP_IDX;
        (yyval.stmt).tbName = (yyvsp[-3].ident);
        (yyval.stmt).colName = (yyvsp[-1].ident);
    }
#line 1563 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 169 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = EXIT_ST;
    }
#line 1571 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 173 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = CLOSE_ST;
    }
#line 1579 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 177 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.stmt).id = SHOW_TABLE_ID;
        (yyval.stmt).tbName = (yyvsp[0].ident);
    }
#line 1588 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 184 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.field_list).clear();
        (yyval.field_list).push_back((yyvsp[0].field));
    }
#line 1597 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 189 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.field_list) = (yyvsp[-2].field_list);
        (yyval.field_list).push_back((yyvsp[0].field));
    }
#line 1606 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 195 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.field).id = COL_FIELD;
        (yyval.field).colName = (yyvsp[-1].ident);
        (yyval.field).type = (yyvsp[0].type);
    }
#line 1616 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 201 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.field).id = NOTNULL_COL_FIELD;
        (yyval.field).colName = (yyvsp[-3].ident);
        (yyval.field).type = (yyvsp[-2].type);
    }
#line 1626 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 207 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.field).id = PRIMARY_FIELD;
        (yyval.field).colList = (yyvsp[-1].column_list);
            // TODO : Columnlist
    }
#line 1636 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 213 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.field).id = FOREIGN_FIELD;
        (yyval.field).colName = (yyvsp[-6].ident);
        (yyval.field).tbName = (yyvsp[-3].ident);
        (yyval.field).refcolName = (yyvsp[-1].ident);
    }
#line 1647 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 222 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.type).id = INT_TYPE;
            (yyval.type).length = 4;
    }
#line 1656 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 227 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.type).id = VARCHAR_TYPE;
            (yyval.type).length = MAXNAME + 1;
    }
#line 1665 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 232 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.type).id = INT_TYPE;
            (yyval.type).length = 4;
    }
#line 1674 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 237 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.type).id = VARCHAR_TYPE;
        (yyval.type).length = (yyvsp[-1].value_int) + 3;
    }
#line 1683 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 242 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.type).id = VARCHAR_TYPE;
        (yyval.type).length = (yyvsp[-1].value_int) + 3;
    }
#line 1692 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 247 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.type).id = DATE_TYPE;
            (yyval.type).length = 4;
    }
#line 1701 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 252 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.type).id = FLOAT_TYPE;
            (yyval.type).length = 4;
    }
#line 1710 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 259 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.value_lists).clear();
        (yyval.value_lists).push_back((yyvsp[-1].value_list));
    }
#line 1719 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 264 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.value_lists) = std::move((yyvsp[-4].value_lists));
        (yyval.value_lists).push_back(std::move((yyvsp[-1].value_list)));
    }
#line 1728 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 271 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.value_list).clear();
        (yyval.value_list).push_back((yyvsp[0].value));
    }
#line 1737 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 276 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.value_list) = (yyvsp[-2].value_list);
        (yyval.value_list).push_back((yyvsp[0].value));
    }
#line 1746 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 283 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.value).id = VALUE_INT_ID;
        (yyval.value).value_int = (yyvsp[0].value_int);
    }
#line 1755 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 288 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.value).id = VALUE_STRING_ID;
        (yyval.value).value_string = (yyvsp[0].value_string);
    }
#line 1764 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 293 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.value).id = VALUE_FLOAT_ID;
        (yyval.value).value_float = (yyvsp[0].value_float);
    }
#line 1773 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 298 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.value).id = VALUE_DATE_ID;
        (yyval.value).value_string = (yyvsp[0].value_string);
    }
#line 1782 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 303 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.value).id = VALUE_NULL_ID;
    }
#line 1790 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 309 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.where_list) = (yyvsp[0].where_list);
    }
#line 1798 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 313 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.where_list).clear();
    }
#line 1806 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 318 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.where_list).clear();
        (yyval.where_list).push_back((yyvsp[0].where));
    }
#line 1815 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 323 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.where_list) = (yyvsp[-2].where_list);
        (yyval.where_list).push_back((yyvsp[0].where));
    }
#line 1824 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 330 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.where).id = COL_V_WHERECLAUSE;
        (yyval.where).fi = (yyvsp[-2].col);
        (yyval.where).oper = (yyvsp[-1].oper);
        (yyval.where).sval = (yyvsp[0].value);
    }
#line 1835 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 337 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.where).id = COL_C_WHERECLAUSE;
        (yyval.where).fi = (yyvsp[-2].col);
        (yyval.where).oper = (yyvsp[-1].oper);
        (yyval.where).scol = (yyvsp[0].col);
    }
#line 1846 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 344 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.where).id = COL_ISNULL_WHERECLAUSE;
        (yyval.where).fi = (yyvsp[-2].col);
    }
#line 1855 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 349 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.where).id = COL_ISNOTNULL_WHERECLAUSE;
        (yyval.where).fi = (yyvsp[-3].col);
    }
#line 1864 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 354 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.where).id = COL_LIKECLAUSE;
        (yyval.where).fi = (yyvsp[-2].col);
        (yyval.where).pattern = (yyvsp[0].value_string);
    }
#line 1874 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 360 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.where).id = COL_NOTLIKECLAUSE;
        (yyval.where).fi = (yyvsp[-3].col);
        (yyval.where).pattern = (yyvsp[0].value_string);
    }
#line 1884 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 368 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.oper) = EQ_OPER;
    }
#line 1892 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 372 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.oper) = NEQ_OPER;
    }
#line 1900 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 376 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.oper) = LEQ_OPER;
    }
#line 1908 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 380 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.oper) = GEQ_OPER;
    }
#line 1916 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 384 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.oper) = LT_OPER;
    }
#line 1924 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 388 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.oper) = GT_OPER;
    }
#line 1932 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 394 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.setcl).colName = (yyvsp[-2].ident);
        (yyval.setcl).value = (yyvsp[0].value);
    }
#line 1941 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 401 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.setcl_list).clear();
        (yyval.setcl_list).push_back((yyvsp[0].setcl));
    }
#line 1950 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 406 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.setcl_list) = (yyvsp[-2].setcl_list);
        (yyval.setcl_list).push_back((yyvsp[0].setcl));
    }
#line 1959 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 413 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.sel).col_list.clear();
    }
#line 1967 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 417 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sel).col_list = (yyvsp[0].col_list);
    }
#line 1975 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 423 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.col).flag = 0;
            (yyval.col).aggtype = 0;
        (yyval.col).colName = (yyvsp[0].ident);
    }
#line 1985 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 429 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.col).flag = 1;
            (yyval.col).aggtype = 0;
        (yyval.col).tbName = (yyvsp[-2].ident);
        (yyval.col).colName = (yyvsp[0].ident);
    }
#line 1996 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 438 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.col) = (yyvsp[0].col);
            (yyval.col).aggtype = 0;
    }
#line 2005 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 443 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.col) = (yyvsp[-1].col);
            (yyval.col).aggtype = AGG_SUM;
    }
#line 2014 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 448 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.col) = (yyvsp[-1].col);
            (yyval.col).aggtype = AGG_AVG;
    }
#line 2023 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 453 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.col) = (yyvsp[-1].col);
            (yyval.col).aggtype = AGG_MAX;
    }
#line 2032 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 458 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.col) = (yyvsp[-1].col);
            (yyval.col).aggtype = AGG_MIN;
    }
#line 2041 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 465 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.col_list).clear();
        (yyval.col_list).push_back((yyvsp[0].col));
    }
#line 2050 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 470 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.col_list) = (yyvsp[-2].col_list);
        (yyval.col_list).push_back((yyvsp[0].col));
    }
#line 2059 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 477 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.col_list).clear();
        (yyval.col_list).push_back((yyvsp[0].col));
    }
#line 2068 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 482 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.col_list) = (yyvsp[-2].col_list);
        (yyval.col_list).push_back((yyvsp[0].col));
    }
#line 2077 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 489 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.col_list).clear();
        (yyval.col_list).push_back((yyvsp[0].col));
    }
#line 2086 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 494 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.col_list) = (yyvsp[-2].col_list);
        (yyval.col_list).push_back((yyvsp[0].col));
    }
#line 2095 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 501 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.col) = (yyvsp[-1].col);
            (yyval.col).ordtype = ORDER_BY_DEC;
    }
#line 2104 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 506 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.col) = (yyvsp[-1].col);
            (yyval.col).ordtype = ORDER_BY_INC;
    }
#line 2113 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 511 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.col) = (yyvsp[0].col);
            (yyval.col).ordtype = ORDER_BY_INC;
    }
#line 2122 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 518 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.table_list).clear();
        (yyval.table_list).push_back((yyvsp[0].ident));
    }
#line 2131 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 523 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.table_list) = (yyvsp[-2].table_list);
        (yyval.table_list).push_back((yyvsp[0].ident));
    }
#line 2140 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 530 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.column_list).clear();
        (yyval.column_list).push_back((yyvsp[0].ident));
    }
#line 2149 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 535 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.column_list) = (yyvsp[-2].column_list);
        (yyval.column_list).push_back((yyvsp[0].ident));
    }
#line 2158 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 542 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.col_list).clear();
    }
#line 2166 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 546 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.col_list) = (yyvsp[0].col_list);
    }
#line 2174 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 551 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.col_list).clear();
    }
#line 2182 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 555 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.col_list) = (yyvsp[0].col_list);
    }
#line 2190 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 560 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.fileout).if_csv = 0;
    }
#line 2198 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 564 "yacc.y" /* yacc.c:1646  */
    {
            (yyval.fileout).if_csv = 1;
        (yyval.fileout).fileName = (yyvsp[0].value_string);
    }
#line 2207 "yacc.tab.c" /* yacc.c:1646  */
    break;


#line 2211 "yacc.tab.c" /* yacc.c:1646  */
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
          yydestruct("Error: discarding",
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
        yydestruct("Cleanup: discarding lookahead",
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

#line 569 "yacc.y" /* yacc.c:1906  */
  

void yyerror(const char *s)
{
    parserError = 1;
    //std::cerr << s << std::endl;
}  



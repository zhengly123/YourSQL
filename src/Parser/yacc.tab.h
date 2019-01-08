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

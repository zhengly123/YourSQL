/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
#define QOUTPUT 311
#define QMIN 312
#define QMAX 313
#define QAVG 314
#define QSUM 315
#define QCHAR 316
#define ORDERBY 317
#define GROUPBY 318
#define ASC 319




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


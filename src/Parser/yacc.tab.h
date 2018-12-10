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
     INTEGER = 258,
     IDENTIFIER = 259,
     OPERATOR = 260,
     DATABASE = 261,
     DATABASES = 262,
     DROP = 263,
     USE = 264,
     INSERT = 265,
     INTO = 266,
     UPDATE = 267,
     SET = 268,
     DESC = 269,
     REFERENCES = 270,
     INDEX = 271,
     TABLE = 272,
     TABLES = 273,
     SHOW = 274,
     CREATE = 275,
     PRIMARY = 276,
     KEY = 277,
     NOT = 278,
     MYNULL = 279,
     VALUES = 280,
     DELETE = 281,
     FROM = 282,
     WHERE = 283,
     SELECT = 284,
     IS = 285,
     MINT = 286,
     VARCHAR = 287,
     AND = 288,
     DATE = 289,
     MFLOAT = 290,
     FOREIGN = 291,
     ERROR = 292,
     EQ = 293,
     NEQ = 294,
     LEQ = 295,
     GEQ = 296,
     LT = 297,
     GTs = 298,
     LB = 299,
     RB = 300,
     FH = 301,
     DH = 302
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define IDENTIFIER 259
#define OPERATOR 260
#define DATABASE 261
#define DATABASES 262
#define DROP 263
#define USE 264
#define INSERT 265
#define INTO 266
#define UPDATE 267
#define SET 268
#define DESC 269
#define REFERENCES 270
#define INDEX 271
#define TABLE 272
#define TABLES 273
#define SHOW 274
#define CREATE 275
#define PRIMARY 276
#define KEY 277
#define NOT 278
#define MYNULL 279
#define VALUES 280
#define DELETE 281
#define FROM 282
#define WHERE 283
#define SELECT 284
#define IS 285
#define MINT 286
#define VARCHAR 287
#define AND 288
#define DATE 289
#define MFLOAT 290
#define FOREIGN 291
#define ERROR 292
#define EQ 293
#define NEQ 294
#define LEQ 295
#define GEQ 296
#define LT 297
#define GTs 298
#define LB 299
#define RB 300
#define FH 301
#define DH 302




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


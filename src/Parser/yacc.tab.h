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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


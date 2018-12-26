%{  

/* 1. Statement */

#include "parser.h"

extern "C"
{
    void yyerror(const char *s);  
    extern int yylex(void);
}

int parserError;
ASType toplevel;

%}  

%token<value_int> VALUE_INT
%token<value_string> VALUE_STRING
%token<ident> IDENTIFIER  
%token OPERATOR

%token DATABASE DATABASES 
%token DROP USE INSERT INTO UPDATE SET DESC 
%token REFERENCES INDEX TABLE TABLES SHOW 
%token CREATE PRIMARY KEY NOT MYNULL VALUES DELETE 
%token FROM WHERE SELECT IS MINT VARCHAR AND DATE MFLOAT FOREIGN
%token ERROR
%token EQ NEQ LEQ GEQ LT GT
%token LB RB FH DH DOT STAR
%token QEXIT

/* %type Program
%type Stmt */

%type<stmt_list> CommandList
%type<stmt> Stmt
%type<field_list> FieldList
%type<field> Field
%type<type> Type
%type<value> Value
%type<value_list> ValueList
%type<value_lists> ValueLists
%type<where_list> WhereClause
%type<where> WhereSubClause
%type<oper> Oper
%type<setcl> SetClause
%type<setcl_list> SetClauseList
%type<sel> Selector
%type<col> Col
%type<col_list> ColList
%type<table_list> TableList
%type<column_list> ColumnList

%start Program

%%  

Program : CommandList
        {
            toplevel.stmt_list = $1;
        }
;

CommandList :  /* empty */
        {
            $$.clear();
        }
        | CommandList Stmt
        {
            $$ = $1;
            $$.push_back($2);
        }
;

Stmt    : SHOW DATABASES
        {
            $$.id = SHOW_DB;
        }
        | CREATE DATABASE IDENTIFIER
        {
            $$.id = CREATE_DB;
            $$.dbName = $3;
        }
        | DROP DATABASE IDENTIFIER
        {
            $$.id = DROP_DB;
            $$.dbName = $3;
        }
        | USE IDENTIFIER
        {
            $$.id = USE_DB;
            $$.dbName = $2;
        }
        | SHOW TABLES
        {
            $$.id = SHOW_TABLE;
        }
        | CREATE TABLE IDENTIFIER LB FieldList RB
        {
            $$.id = CREATE_TABLE;
            $$.tbName = $3;
            $$.field_list = $5;
        }
        | DROP TABLE IDENTIFIER
        {
            $$.id = DROP_TABLE;
            $$.tbName = $3;
        }
        | DESC IDENTIFIER
        {
            $$.id = DESC_ST;
            $$.tbName = $2;
        }
        | INSERT INTO IDENTIFIER VALUES ValueLists
        {
            $$.id = INSERT_ST;
            $$.tbName = $3;
            $$.value_lists = $5;
        }
        | DELETE FROM IDENTIFIER WHERE WhereClause
        {
            $$.id = DELETE_ST;
            $$.tbName = $3;
            $$.where_list = $5;
        }
        | UPDATE IDENTIFIER SET SetClauseList WHERE WhereClause
        {
            $$.id = UPDATE_ST;
            $$.tbName = $2;
            $$.setcl_list = $4;
            $$.where_list = $6;
        }
        | SELECT Selector FROM TableList WHERE WhereClause
        {
            $$.id = SELECT_ST;
            $$.sel = $2;
            $$.table_list = $4;
            $$.where_list = $6;
        }
        | CREATE INDEX IDENTIFIER LB IDENTIFIER RB
        {
            $$.id = CREATE_IDX;
            $$.tbName = $3;
            $$.colName = $5;
        }
        | DROP INDEX IDENTIFIER LB IDENTIFIER RB
        {
            $$.id = DROP_IDX;
            $$.tbName = $3;
            $$.colName = $5;
        }
        | QEXIT
        {
            $$.id = EXIT_ST;
        }
;

FieldList : Field
        {
            $$.clear();
            $$.push_back($1);
        }
        | FieldList DH Field
        {
            $$ = $1;
            $$.push_back($3);
        }

Field   : IDENTIFIER Type
        {
            $$.id = COL_FIELD;
            $$.colName = $1;
            $$.type = $2;
        }
        | IDENTIFIER Type NOT MYNULL
        {
            $$.id = NOTNULL_COL_FIELD;
            $$.colName = $1;
            $$.type = $2;
        }
        | PRIMARY KEY LB ColumnList RB
        {
            $$.id = PRIMARY_FIELD;
            $$.colList = $4;
            // TODO : Columnlist
        }
        | FOREIGN KEY LB IDENTIFIER RB REFERENCES IDENTIFIER LB IDENTIFIER RB
        {
            $$.id = FOREIGN_FIELD;
            $$.colName = $4;
            $$.tbName = $7;
            $$.refcolName = $9;
        }
;

Type    : MINT
        {
            $$.id = INT_TYPE;
        }
        | VARCHAR
        {
            $$.id = VARCHAR_TYPE;
        }
        | MINT VALUE_INT
        {
            $$.id = INT_CONST_TYPE;
            $$.value_int = $2;
        }
        | VARCHAR VALUE_INT
        {
            $$.id = VARCHAR_CONST_TYPE;
            $$.value_int = $2;
        }
        | DATE
        {
            $$.id = DATE_TYPE;
        }
        | MFLOAT
        {
            $$.id = FLOAT_TYPE;
        }
;

ValueLists : LB ValueList RB
        {
            $$.clear();
            $$.push_back($2);            
        }
        | ValueLists DH LB ValueList RB
        {
            $$ = $1;
            $$.push_back($4);
        }
;

ValueList: Value
        {
            $$.clear();
            $$.push_back($1);
        }
        | ValueList DH Value
        {
            $$ = $1;
            $$.push_back($3);
        }
;

Value   : VALUE_INT
        {
            $$.id = VALUE_INT_ID;
            $$.value_int = $1;
        }
        | VALUE_STRING
        {
            $$.id = VALUE_STRING_ID;
            $$.value_string = $1;
        }
        | MYNULL
        {
            $$.id = VALUE_NULL_ID;
        }
;

WhereClause : WhereSubClause
        {
            $$.clear();
            $$.push_back($1);
        }
        | WhereClause AND WhereSubClause
        {
            $$ = $1;
            $$.push_back($3);
        }
;

WhereSubClause : Col Oper Value
        {
            $$.id = COL_V_WHERECLAUSE;
            $$.fi = $1;
            $$.oper = $2;
            $$.sval = $3;
        }
        | Col Oper Col
        {
            $$.id = COL_C_WHERECLAUSE;
            $$.fi = $1;
            $$.oper = $2;
            $$.scol = $3;
        }
        | Col IS MYNULL
        {
            $$.id = COL_ISNULL_WHERECLAUSE;
            $$.fi = $1;
        }
        | Col IS NOT MYNULL
        {
            $$.id = COL_ISNOTNULL_WHERECLAUSE;
            $$.fi = $1;
        }
;

Oper    : EQ
        {
            $$ = EQ_OPER;
        }
        | NEQ
        {
            $$ = NEQ_OPER;
        }
        | LEQ
        {
            $$ = LEQ_OPER;
        }
        | GEQ
        {
            $$ = GEQ_OPER;
        }
        | LT
        {
            $$ = LT_OPER;
        }
        | GT
        {
            $$ = GT_OPER;
        }
;

SetClause: IDENTIFIER EQ Value
        {
            $$.colName = $1;
            $$.value = $3;
        }
;

SetClauseList : SetClause
        {
            $$.clear();
            $$.push_back($1);    
        }
        | SetClauseList DH SetClause
        {
            $$ = $1;
            $$.push_back($3);
        }
;

Selector: STAR
        {
            $$.col_list.clear();
        }
        | ColList
        {
            $$.col_list = $1;
        }
;

Col     : IDENTIFIER
        {
            $$.flag = 0;
            $$.colName = $1;
        }
        | IDENTIFIER DOT IDENTIFIER
        {
            $$.flag = 1;
            $$.tbName = $1;
            $$.colName = $3;
        }
;

ColList : Col
        {
            $$.clear();
            $$.push_back($1);            
        }
        | ColList DH Col
        {
            $$ = $1;
            $$.push_back($3);
        }
;

TableList: IDENTIFIER
        {
            $$.clear();
            $$.push_back($1);
        }
        | TableList DH IDENTIFIER
        {
            $$ = $1;
            $$.push_back($3);
        }
;

ColumnList: IDENTIFIER
        {
            $$.clear();
            $$.push_back($1);
        }
        | ColumnList DH IDENTIFIER
        {
            $$ = $1;
            $$.push_back($3);
        }
;

%%  

void yyerror(const char *s)
{
    parserError = 1;
    //std::cerr << s << std::endl;
}  



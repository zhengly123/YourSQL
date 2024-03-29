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
%token<value_float> VALUE_FLOAT
%token<value_string> VALUE_DATE
%token<ident> IDENTIFIER  
%token OPERATOR

%token DATABASE DATABASES 
%token DROP USE INSERT INTO UPDATE SET DESC 
%token REFERENCES INDEX TABLE TABLES SHOW 
%token CREATE PRIMARY KEY NOT MYNULL VALUES DELETE 
%token FROM WHERE SELECT IS MINT VARCHAR AND DATE MFLOAT FOREIGN
%token ERROR GLIKE
%token EQ NEQ LEQ GEQ LT GT
%token LB RB FH DH DOT STAR
%token QEXIT QCLOSE QOUTPUT
%token QMIN QMAX QAVG QSUM QCHAR
%token ORDERBY GROUPBY ASC

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
%type<where_list> WhereClauseX
%type<where> WhereSubClause
%type<oper> Oper
%type<setcl> SetClause
%type<setcl_list> SetClauseList
%type<sel> Selector
%type<col> Col
%type<col> ACol
%type<col> OCol
%type<col_list> ColList
%type<col_list> AColList
%type<col_list> OColList
%type<col_list> OrderByClause
%type<col_list> GroupByClause
%type<fileout> OutputClause
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
        | DELETE FROM IDENTIFIER WhereClauseX
        {
            $$.id = DELETE_ST;
            $$.tbName = $3;
            $$.where_list = $4;
        }
        | UPDATE IDENTIFIER SET SetClauseList WhereClauseX
        {
            $$.id = UPDATE_ST;
            $$.tbName = $2;
            $$.setcl_list = $4;
            $$.where_list = $5;
        }
        | SELECT Selector FROM TableList WhereClauseX GroupByClause OrderByClause OutputClause
        {
            $$.id = SELECT_ST;
            $$.sel = $2;
            $$.table_list = $4;
            $$.where_list = $5;
            $$.group_list = $6;
            $$.order_list = $7;
            $$.fileout = $8;
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
        | QCLOSE
        {
            $$.id = CLOSE_ST;
        }
        | SHOW TABLE IDENTIFIER
        {
            $$.id = SHOW_TABLE_ID;
            $$.tbName = $3;
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
            $$.length = 4;
        }
        | VARCHAR
        {
            $$.id = VARCHAR_TYPE;
            $$.length = MAXNAME + 1;
        }
        | MINT LB VALUE_INT RB
        {
            $$.id = INT_TYPE;
            $$.length = 4;
        }
        | VARCHAR LB VALUE_INT RB
        {
            $$.id = VARCHAR_TYPE;
            $$.length = $3 + 3;
        }
        | QCHAR LB VALUE_INT RB
        {
            $$.id = VARCHAR_TYPE;
            $$.length = $3 + 3;
        }
        | DATE
        {
            $$.id = DATE_TYPE;
            $$.length = 4;
        }
        | MFLOAT
        {
            $$.id = FLOAT_TYPE;
            $$.length = 4;
        }
;

ValueLists : LB ValueList RB
        {
            $$.clear();
            $$.push_back($2);            
        }
        | ValueLists DH LB ValueList RB
        {
            $$ = std::move($1);
            $$.push_back(std::move($4));
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
        | VALUE_FLOAT
        {
            $$.id = VALUE_FLOAT_ID;
            $$.value_float = $1;
        }
        | VALUE_DATE
        {
            $$.id = VALUE_DATE_ID;
            $$.value_string = $1;
        }
        | MYNULL
        {
            $$.id = VALUE_NULL_ID;
        }
;

WhereClauseX : WHERE WhereClause
        {
            $$ = $2;
        }
        | /* empty */
        {
            $$.clear();
        }

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
        | Col GLIKE VALUE_STRING
        {
            $$.id = COL_LIKECLAUSE;
            $$.fi = $1;
            $$.pattern = $3;
        }
        | Col NOT GLIKE VALUE_STRING
        {
            $$.id = COL_NOTLIKECLAUSE;
            $$.fi = $1;
            $$.pattern = $4;
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
        | AColList
        {
            $$.col_list = $1;
        }
;

Col     : IDENTIFIER
        {
            $$.flag = 0;
            $$.aggtype = 0;
            $$.colName = $1;
        }
        | IDENTIFIER DOT IDENTIFIER
        {
            $$.flag = 1;
            $$.aggtype = 0;
            $$.tbName = $1;
            $$.colName = $3;
        }
;

ACol    : Col
        {
            $$ = $1;
            $$.aggtype = 0;
        }
        | QSUM LB Col RB
        {
            $$ = $3;
            $$.aggtype = AGG_SUM;
        }
        | QAVG LB Col RB
        {
            $$ = $3;
            $$.aggtype = AGG_AVG;
        }
        | QMAX LB Col RB
        {
            $$ = $3;
            $$.aggtype = AGG_MAX;
        }
        | QMIN LB Col RB
        {
            $$ = $3;
            $$.aggtype = AGG_MIN;
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

AColList : ACol
        {
            $$.clear();
            $$.push_back($1);            
        }
        | AColList DH ACol
        {
            $$ = $1;
            $$.push_back($3);
        }
;

OColList : OCol
        {
            $$.clear();
            $$.push_back($1);
        }
        | OColList DH OCol
        {
            $$ = $1;
            $$.push_back($3);
        }
;

OCol    : ACol DESC
        {
            $$ = $1;
            $$.ordtype = ORDER_BY_DEC;
        }
        | ACol ASC
        {
            $$ = $1;
            $$.ordtype = ORDER_BY_INC;
        }
        | ACol
        {
            $$ = $1;
            $$.ordtype = ORDER_BY_INC;
        }


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

OrderByClause : /* empty */
        {
            $$.clear();
        }
        | ORDERBY OColList
        {
            $$ = $2;
        }

GroupByClause : /* empty */
        {
            $$.clear();
        }
        | GROUPBY ColList
        {
            $$ = $2;
        }

OutputClause : /* empty */
        {
            $$.if_csv = 0;
        }
        | QOUTPUT VALUE_STRING
        {
            $$.if_csv = 1;
            $$.fileName = $2;
        }

%%  

void yyerror(const char *s)
{
    parserError = 1;
    //std::cerr << s << std::endl;
}  



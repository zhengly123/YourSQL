#ifndef PARSER_H
#define PARSER_H

#include <cstring>
#include <iostream>
#include <stdio.h>
#include <list>

struct itype
{
    int id;
    int value_int;
};

struct ivalue
{
	int id;
	int value_int;
	std::string value_string;
};

struct isetcl
{
	std::string colName;
	ivalue value;
};

struct icol
{
	int flag;
	// 0 : No  tbName
	// 1 : Has tbName
	std::string tbName;
	std::string colName;
};

struct isel
{
    std::list<icol> col_list;
    // empty list : *
    // un-empty list : col_list
};

struct iwhere
{
	int id;
	icol fi, scol;
	int oper;
	ivalue sval;
};

struct ifield
{
	int id;
	std::string colName;
	itype type;
	std::string tbName, refcolName;
	std::list<std::string> colList;
};

struct istmt
{
	int id;
	std::string dbName;
	std::string tbName;
	std::list<ifield> field_list;
	std::list<std::list<ivalue>> value_lists;
	std::list<iwhere> where_list;
	std::list<isetcl> setcl_list;
	std::list<std::string> table_list;
	isel sel;
	std::string colName;
};

struct ASType
{
	std::string ident;
    int value_int;  
   	std::string value_string;

    itype type;

    ifield field;
    std::list<ifield> field_list;

    istmt stmt;
    std::list<istmt> stmt_list;

    std::list<std::string> column_list;
    std::list<std::string> table_list;

    icol col;
    std::list<icol> col_list;
    isel sel;

    isetcl setcl;
    std::list<isetcl> setcl_list;

    int oper;

    iwhere where;
    std::list<iwhere> where_list;

    ivalue value;
    std::list<ivalue> value_list;
    std::list<std::list<ivalue>> value_lists;
};

#define YYSTYPE ASType

const int STMT_START = 0;
const int SHOW_DB = STMT_START + 1;
const int CREATE_DB = SHOW_DB + 1;
const int DROP_DB = CREATE_DB + 1;
const int USE_DB = DROP_DB + 1;
const int SHOW_TABLE = USE_DB + 1;
const int CREATE_TABLE = SHOW_TABLE + 1;
const int DROP_TABLE = CREATE_TABLE + 1;
const int DESC_ST = DROP_TABLE + 1;
const int INSERT_ST = DESC_ST + 1;
const int DELETE_ST = INSERT_ST + 1;
const int UPDATE_ST = DELETE_ST + 1;
const int SELECT_ST = UPDATE_ST + 1;
const int CREATE_IDX = SELECT_ST + 1;
const int DROP_IDX = CREATE_IDX + 1;

const int INT_TYPE = DROP_IDX + 1;
const int INT_CONST_TYPE = INT_TYPE + 1;
const int VARCHAR_TYPE = INT_CONST_TYPE + 1;
const int VARCHAR_CONST_TYPE = VARCHAR_TYPE + 1;
const int DATE_TYPE = VARCHAR_CONST_TYPE + 1;
const int FLOAT_TYPE = DATE_TYPE + 1;

const int COL_FIELD = FLOAT_TYPE + 1;
const int NOTNULL_COL_FIELD = COL_FIELD + 1;
const int PRIMARY_FIELD = NOTNULL_COL_FIELD + 1;
const int FOREIGN_FIELD = PRIMARY_FIELD + 1;

const int VALUE_INT_ID = FOREIGN_FIELD + 1;
const int VALUE_STRING_ID = VALUE_INT_ID + 1;
const int VALUE_NULL_ID = VALUE_STRING_ID + 1;

const int EQ_OPER = VALUE_NULL_ID + 1;
const int NEQ_OPER = EQ_OPER + 1;
const int LEQ_OPER = NEQ_OPER + 1;
const int GEQ_OPER = LEQ_OPER + 1;
const int LT_OPER = GEQ_OPER + 1;
const int GT_OPER = LT_OPER + 1;

const int COL_V_WHERECLAUSE = GT_OPER + 1;
const int COL_C_WHERECLAUSE = COL_V_WHERECLAUSE + 1;
const int COL_ISNULL_WHERECLAUSE = COL_C_WHERECLAUSE + 1;
const int COL_ISNOTNULL_WHERECLAUSE = COL_ISNULL_WHERECLAUSE + 1;

#endif
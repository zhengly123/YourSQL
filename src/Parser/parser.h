#ifndef PARSER_H
#define PARSER_H

#include <cstring>
#include <iostream>
#include <stdio.h>
#include <list>

struct istmt
{
	int stmt_type;
	std::string db_name;
};

struct Type
{
	std::string m_sId;
    int m_nInt;  
    char m_cOp;

    istmt stmt_s;
    std::list<istmt> stmt_list;
};

struct AST
{
	std::list<istmt> stmt_list;
};


#define YYSTYPE Type

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

#endif
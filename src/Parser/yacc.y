%{  

/* 1. Statement */

#include "parser.h"

extern "C"
{
    void yyerror(const char *s);  
    extern int yylex(void);
}

AST toplevel;

%}  

%token INTEGER  
%token IDENTIFIER  
%token OPERATOR

%token DATABASE DATABASES 
%token DROP USE INSERT INTO UPDATE SET DESC 
%token REFERENCES INDEX TABLE TABLES SHOW 
%token CREATE PRIMARY KEY NOT MYNULL VALUES DELETE 
%token FROM WHERE SELECT IS MINT VARCHAR AND DATE MFLOAT FOREIGN
%token ERROR
%token EQ NEQ LEQ GEQ LT GTs
%token LB RB FH DH

/* %type Program
%type Stmt */

%start Program

%%  

Program : CommandList
        {
            cout << "Matching Size = " << $1.stmt_list.size() << endl;
            toplevel.stmt_list = $1.stmt_list;
        }
;

CommandList :  /* empty */
        {
            $$.stmt_list.clear();
        }
        | CommandList Stmt FH
        {
            $$.stmt_list = $1.stmt_list;
            $$.stmt_list.push_back($2.stmt_s);
        }
;

Stmt    : SHOW DATABASES
        {
            $$.stmt_s.stmt_type = SHOW_DB;
        }
        | CREATE DATABASE IDENTIFIER
        {
            $$.stmt_s.stmt_type = CREATE_DB;
            $$.stmt_s.db_name = $3.m_sId;
        }
        | DROP DATABASE IDENTIFIER
        {
            $$.stmt_s.stmt_type = DROP_DB;
            $$.stmt_s.db_name = $3.m_sId;
        }
        | USE IDENTIFIER
        {
            $$.stmt_s.stmt_type = USE_DB;
            $$.stmt_s.db_name = $2.m_sId;
        }
        | SHOW TABLES
        {
            $$.stmt_s.stmt_type = SHOW_TABLE;
        }
;

%%  

void yyerror(const char *s)
{  
    cerr<<s<<endl;
}  



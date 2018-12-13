
%{  

// 1 . Statement 

#include "parser.h"
#include "yacc.tab.h"

extern "C"
{
    int yywrap(void);  
    int yylex(void); // from Lex  
}  

%}  

%option case-insensitive

nondigit    ([_A-Za-z])  
digit       ([0-9])
integer     ({digit}+)  
identifier  ({nondigit}({nondigit}|{digit})*)
string		('({nondigit}|{digit})*')
blank_chars ([ \f\r\t\v\n]+)

/* 2 . Regular */

%%  

"DATABASE"		{return DATABASE;}
"DATABASES"		{return DATABASES;}
"DROP"			{return DROP;}
"USE"			{return USE;}
"INSERT"		{return INSERT;}
"INTO"			{return INTO;}
"UPDATE"		{return UPDATE;}
"SET"			{return SET;}
"DESC"			{return DESC;}
"REFERENCES"	{return REFERENCES;}
"INDEX"			{return INDEX;}
"TABLE"			{return TABLE;}
"TABLES"		{return TABLES;}
"SHOW"			{return SHOW;}
"CREATE"		{return CREATE;}
"PRIMARY"		{return PRIMARY;}
"KEY"			{return KEY;}
"NOT"			{return NOT;}
"NULL"			{return MYNULL;}
"VALUES"		{return VALUES;}
"DELETE"		{return DELETE;}
"FROM"			{return FROM;}
"WHERE"			{return WHERE;}
"SELECT"		{return SELECT;}
"IS"			{return IS;}
"INT"			{return MINT;}
"VARCHAR"		{return VARCHAR;}
"AND"			{return AND;}
"DATE"			{return DATE;}
"FLOAT"			{return MFLOAT;}
"FOREIGN"		{return FOREIGN;}

{identifier}    {yylval.ident = yytext; return IDENTIFIER;}
{integer}		{yylval.value_int = atoi(yytext);return VALUE_INT;}
{string}		{yylval.value_string = yytext; return VALUE_STRING;}
{blank_chars}   {}

"="				{return EQ;}
"<>"			{return NEQ;}
"<="			{return LEQ;}
">="			{return GEQ;}
"<"				{return LT;}
">"				{return GT;}
"("				{return LB;}
")"				{return RB;}
";"				{return FH;}
","				{return DH;}
"."				{return DOT;}
"*"				{return STAR;}
.       		{}

%% 

/* 3 . C Funtion  */
int yywrap(void)  
{  
    return 1;
}  

%{  

// 1 . Statement 

#include "parser.h"
#include "yacc.tab.h"

extern "C"
{
    int yywrap(void);  
    int yylex(void); // from Lex  
}  

static std::string string_buf;

%}  

%option case-insensitive

nondigit    ([_A-Za-z])  
digit       ([0-9])
integer     ({digit}+)
minteger    (-{integer})
float       ({integer}\.{integer})
mfloat      (-{float})
date        ('[0-9]{4}-[0-9]{2}-[0-9]{2}')
identifier  ({nondigit}({nondigit}|{digit})*)
/* string		('({nondigit}|{digit}|[\%_\[\]^ \-\.])*') */
/* string      ('[^\n]+') */
strtext     ([^\\\n\']+)
linend      ([\n\r])
blank_chars ([ \f\r\t\v\n]+)

%x str

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
"ASC"           {return ASC;}
"REFERENCES"	{return REFERENCES;}
"INDEX"			{return INDEX;}
"TABLE"			{return TABLE;}
"TABLES"		{return TABLES;}
"SHOW"			{return SHOW;}
"CREATE"		{return CREATE;}
"CHAR"          {return QCHAR;}
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
"EXIT"          {return QEXIT;}
"CLOSE"         {return QCLOSE;}
"MIN"           {return QMIN;}
"MAX"           {return QMAX;}
"SUM"           {return QSUM;}
"AVG"           {return QAVG;}
"ORDER BY"      {return ORDERBY;}
"GROUP BY"      {return GROUPBY;}
"LIKE"          {return GLIKE;}

{identifier}    {yylval.ident = yytext; return IDENTIFIER;}
{mfloat}        {yylval.value_float = atof(yytext); return VALUE_FLOAT;}
{float}         {yylval.value_float = atof(yytext); return VALUE_FLOAT;}
{minteger}      {yylval.value_int = atoi(yytext);return VALUE_INT;}
{integer}		{yylval.value_int = atoi(yytext);return VALUE_INT;}
{date}          {yylval.value_string = yytext; return VALUE_DATE;}
{blank_chars}   {}

"="				{return EQ;}
"<>"			{return NEQ;}
"<="			{return LEQ;}
">="			{return GEQ;}
"<"				{return LT;}
">"				{return GT;}
"("				{return LB;}
")"				{return RB;}
";"				{yyterminate(); return FH;}
","				{return DH;}
"."				{return DOT;}
"*"				{return STAR;}

"'"             {string_buf = "'"; BEGIN(str);}
<str>"'"        {string_buf = string_buf + "'"; yylval.value_string = string_buf; BEGIN(INITIAL); return VALUE_STRING;}
<str>"\\'"       {string_buf = string_buf + '\'';}
<str>{strtext} {string_buf = string_buf + yytext;}

.       		{}


%% 

/* 3 . C Funtion  */
int yywrap(void)  
{  
    return 1;
}  
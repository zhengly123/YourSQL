//
// Created by 杨乐 on 2018/12/10.
//

#ifndef YOURSQL_ASTREE_H
#define YOURSQL_ASTREE_H

#include "parser.h"

#include "../SM/SM_PUBLIC.h"
#include <iostream>

void tester(int ident, std::string);

void stmtparser(SM_Manager &smm, istmt st);
void treeparser(SM_Manager &smm);
void fieldparser(ifield fd);
void fieldlistparser(std::list<ifield> fdlist);

void valuelistsparser(std::list<std::list<ivalue>> valuelists);
void valuelistparser(std::list<ivalue> valuelist);
void valueparser(ivalue value);

void setclauseparser(isetcl sc);
void setclauselistparser(std::list<isetcl> sclist);

void opparser(int op);
void colparser(icol cl);
void selectorparser(isel sl);
void whereparser(iwhere wh);
void wherelistparser(std::list<iwhere> whlist);

void tableparser(std::list<std::string> table);
std::string typeparser(itype ty);

#endif //YOURSQL_ASTREE_H

//
// Created by 杨乐 on 2018/12/10.
//

#ifndef YOURSQL_ASTREE_H
#define YOURSQL_ASTREE_H

#include "parser.h"
#include "../yoursql.h"

#include "../SM/SM_PUBLIC.h"
#include "../QL/QL_PUBLIC.h"
#include <iostream>

static std::string currentDB;

void tester(int ident, std::string);

void stmtparser(SM_Manager &smm, QL_Manager &qlm, istmt st);
void treeparser(SM_Manager &smm, QL_Manager &qlm);
void fieldparser(ifield fd, struct AttrInfo * atrv);
void fieldlistparser(std::list<ifield> fdlist, struct AttrInfo * atrv, int &cnt);

void valuelistparser(std::list<ivalue> valuelist, Value * val);
void valueparser(ivalue value, Value * val);

void setclauseparser(isetcl sc, struct Condition * con);
void setclauselistparser(std::list<isetcl> sclist, struct Condition * con);

CompOp opparser(int op);
void whereparser(iwhere wh, struct Condition * con);
void wherelistparser(std::list<iwhere> whlist, struct Condition * con);
void colparser(icol cl, struct RelAttr * rel);

void selectorparser(isel sl, struct RelAttr * rel);


void tableparser(std::list<std::string> table);
AttrType typeparser(itype ty);

#endif //YOURSQL_ASTREE_H

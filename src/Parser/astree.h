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
static int exitFlag;

void tester(int ident, std::string);

int stmtparser(SM_Manager &smm, QL_Manager &qlm, istmt st);
int treeparser(SM_Manager &smm, QL_Manager &qlm, int flush=1);

int typelength(AttrType ty);
int fieldparser(ifield fd, struct AttrInfo * atrv);
int fieldlistparser(std::list<ifield> fdlist, struct AttrInfo * atrv, int &cnt);

int valuelistparser(std::list<ivalue> valuelist, Value * val);
int valueparser(ivalue value, Value * val);

void setclauseparser(isetcl sc, struct Condition * con);
void setclauselistparser(std::list<isetcl> sclist, struct Condition * con);

CompOp opparser(int op);
void whereparser(iwhere wh, struct Condition * con);
void wherelistparser(std::list<iwhere> whlist, struct Condition * con);
void colparser(icol cl, RelAttr * rel);

void grouplistparser(std::list<icol> grplist, struct RelAttr * rel);
void orderparser(icol cl, RelAttr * rel);
void orderlistparser(std::list<icol> ordlist, struct RelAttr * rel);
void selectorparser(isel sl, struct RelAttr * rel);


void tableparser(std::list<std::string> table);
AttrType typeparser(itype ty);

void clearParser();

#endif //YOURSQL_ASTREE_H

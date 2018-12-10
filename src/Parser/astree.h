//
// Created by 杨乐 on 2018/12/10.
//

#ifndef YOURSQL_ASTREE_H
#define YOURSQL_ASTREE_H

#include "parser.h"

#include "../SM/SM_PUBLIC.h"
#include <iostream>

void stmtparser(SM_Manager &smm, istmt st);
void treeparser(SM_Manager &smm);

#endif //YOURSQL_ASTREE_H

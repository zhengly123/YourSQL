//
// Created by 杨乐 on 2018/12/10.
//

#ifndef YOURSQL_SM_PRIVATE_H
#define YOURSQL_SM_PRIVATE_H

#include "../errorhandle.h"

const int SM_INVALID_DB_NAME = YOURSQL_SM_ERROR_START;
const int SM_NAME_TOO_LONG = SM_INVALID_DB_NAME + 1;
const int SM_SAME_NAME_ATTR = SM_NAME_TOO_LONG + 1;
const int SM_NONEXIST_RELATION = SM_SAME_NAME_ATTR + 1;
const int SM_NONEXIT_ATTR = SM_NONEXIST_RELATION + 1;
const int SM_DB_NOT_CLOSE = SM_NONEXIT_ATTR + 1;
const int SM_ILLEGAL_NAME = SM_DB_NOT_CLOSE + 1;
const int SM_TABLE_EXIST = SM_ILLEGAL_NAME + 1;
const int SM_CLOSE = SM_TABLE_EXIST + 1;
const int SM_FOREIGN_NOTFOUND = SM_CLOSE + 1;
const int SM_FOREIGN_NOTPRIMARY = SM_FOREIGN_NOTFOUND + 1;
const int SM_FOREIGN_TYPEMISMATCH = SM_FOREIGN_NOTPRIMARY + 1;
const int SM_SYSCALL_ERROR = -1;

#endif //YOURSQL_SM_PRIVATE_H

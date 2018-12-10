//
// Created by 杨乐 on 2018/12/10.
//

#ifndef YOURSQL_SM_PUBLIC_H
#define YOURSQL_SM_PUBLIC_H

#include "SM_Manager.h"
const RC SM_INVALID_DB_NAME = 1;
const RC SM_NAME_TOO_LONG = SM_INVALID_DB_NAME + 1;
const RC SM_SAME_NAME_ATTR = SM_NAME_TOO_LONG + 1;

const RC SM_SYSCALL_ERROR = -1;

#endif //YOURSQL_SM_PUBLIC_H

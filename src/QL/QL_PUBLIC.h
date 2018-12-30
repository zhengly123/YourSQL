//
// Created by 杨乐 on 2018/12/10.
//

#ifndef YOURSQL_QL_PUBLIC_H
#define YOURSQL_QL_PUBLIC_H

#include "QL_Manager.h"

const int QL_RELNOTEXIST = 1;
const int QL_INVALIDSIZE = QL_RELNOTEXIST + 1;
const int QL_TYPEUNMATCHED = QL_INVALIDSIZE + 1;
const int QL_ATTRNOTNULL = QL_TYPEUNMATCHED + 1;
const int QL_STRTOOLONG = QL_ATTRNOTNULL + 1;
const int QL_DUPLICATE = QL_STRTOOLONG + 1;
const int QL_CONDITION_INVALID = QL_DUPLICATE + 1;
const int QL_RELNULL = QL_CONDITION_INVALID + 1;
const int QL_RELNOTNULL = QL_RELNULL + 1;
const int QL_AttrNotExist = QL_RELNOTNULL + 1;
const int QL_VALUE_EQPECTED = QL_AttrNotExist + 1;

#endif //YOURSQL_QL_PUBLIC_H

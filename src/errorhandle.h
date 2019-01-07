//
// Created by 杨乐 on 2019/1/5.
//

#ifndef YOURSQL_ERRORHANDLE_H
#define YOURSQL_ERRORHANDLE_H

#include <string>

const int YOURSQL_RM_ERROR_START = 1;
const int YOURSQL_IX_ERROR_START = 101;
const int YOURSQL_SM_ERROR_START = 201;
const int YOURSQL_QL_ERROR_START = 301;
const int YOURSQL_PARSER_ERROR_START = 401;

const std::string rmerror[] =
        {
                "RM_NORECATRID",
                "RM_EOF",
                "RM_BAD_FILESCAN",
        };

const std::string ixerror[] =
        {
                "IX_ITERATOR_TO_END",
                "IX_EMPTY_TREE",
        };

const std::string smerror[] =
        {
                "SM_INVALID_DB_NAME",
                "SM_NAME_TOO_LONG",
                "SM_SAME_NAME_ATTR",
                "SM_NONEXIST_RELATION",
                "SM_NONEXIT_ATTR",
                "SM_DB_NOT_CLOSE",
                "SM_ILLEGAL_NAME",
                "SM_TABLE_EXIST",
                "SM_CLOSE",
                "SM_FOREIGN_NOTFOUND",
                "SM_FOREIGN_NOTPRIMARY",
                "SM_FOREIGN_TYPEMISMATCH",
                "SM_FOREIGN_REF_DROP_ERROR",
                "SM_SYSCALL_ERROR",
        };

const std::string qlerror[] =
        {
                "QL_RELNOTEXIST",
                "QL_INVALIDSIZE",
                "QL_TYPE_MISMATCH",
                "QL_ATTRNOTNULL",
                "QL_STRTOOLONG",
                "QL_DUPLICATE",
                "QL_CONDITION_INVALID",
                "QL_RELNULL",
                "QL_RELNOTNULL",
                "QL_AttrNotExist",
                "QL_VALUE_EQPECTED",
                "QL_GROUPBYERR",
                "QL_WRONGAVGTYPE",
                "QL_PRIMARY_DUPLICATE",
                "QL_FOREIGN_KEY_NOT_FOUND",
        };

const std::string pserror[] =
        {
                "PASERR_MULTIPLE_PRIMARY",
                "PASERR_PRIMARY_NOTFOUND",
                "PASERR_ATTR_TOOLONG",
                "PASERR_FOREIGN_NOTFOUND",
                "PASERR_FOREIGN_MULTIPLE",
                "PASERR_DATE_ERROR",
        };

static std::string errorGet(int rc)
{
    if(rc >= YOURSQL_RM_ERROR_START && rc < YOURSQL_IX_ERROR_START) {return rmerror[rc - YOURSQL_RM_ERROR_START];}
    if(rc >= YOURSQL_IX_ERROR_START && rc < YOURSQL_SM_ERROR_START) {return ixerror[rc - YOURSQL_IX_ERROR_START];}
    if(rc >= YOURSQL_SM_ERROR_START && rc < YOURSQL_QL_ERROR_START) {return smerror[rc - YOURSQL_SM_ERROR_START];}
    if(rc >= YOURSQL_QL_ERROR_START && rc < YOURSQL_PARSER_ERROR_START) {return qlerror[rc - YOURSQL_QL_ERROR_START];}
    if(rc >= YOURSQL_PARSER_ERROR_START) {return pserror[rc - YOURSQL_PARSER_ERROR_START];}
    return "Unrecognized Error";
}

#endif //YOURSQL_ERRORHANDLE_H

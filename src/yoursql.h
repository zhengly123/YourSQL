//
// Created by 杨乐 on 2018/11/5.
//

#ifndef YOURSQL_YOURSQL_H
#define YOURSQL_YOURSQL_H

#include <cassert>
#include <stdint.h>
#include <climits>
#include <float.h>
#include <utility>
#include <string>

using RC = int;
const int MAXNAME = 24;
const int MAXATTRS = 40;
const int PARSEREXIT = -1;

const int AGGREGATE_SUM = 1;
const int AGGREGATE_AVG = AGGREGATE_SUM + 1;
const int AGGREGATE_MIN = AGGREGATE_AVG + 1;
const int AGGREGATE_MAX = AGGREGATE_MIN + 1;

const int ORD_INC = 1;
const int ORD_DEC = ORD_INC + 1;

enum CondType {COND_NORMAL, COND_ISNULL, COND_NOTNULL, COND_LIKE, COND_NOTLIKE};
enum AttrType {INT, FLOAT, STRING, DATETYPE, VARCHR, NULLTYPE, ERRTYPE};
enum CompOp {EQ_OP, NE_OP, LT_OP, GT_OP, LE_OP, GE_OP, NO_OP};

// Pin Strategy Hint
enum ClientHint {
    NO_HINT                                     // default value
};

struct AttrInfo {
    char     attrName[MAXNAME+1]; // Attribute name
    AttrType attrType;            // Type of attribute
    int      attrLength;          // Length of attribute
    int      offset;
    char     relName[MAXNAME+1];
    int      flag;                // 1 : not null; 2 : primary key; 3 : not null & primary key
    int      indexNum;
    int      nullOffset;             // attrNum-th attr in the relation
    int      aggregateFunc;
    bool isNotNull(){ return (flag & 1) > 0; }
};

using RelAttrType = std::pair<std::string, std::string>;

struct RelAttr {
  char *relName;     // relation name (may be NULL)
  char *attrName;    // attribute name

  int op;
    // aggregate function type
    // 0: no aggregate function
    // AGGREGATE_SUM : sum
    // AGGREGATE_AVG : avg
    // AGGREGATE_MIN : min
    // AGGREGATE_MAX : max

  int ord;
    // order
    // ORD_INC : increase
    // ORD_DEC : decrease
};

struct Value {
  AttrType type;     // type of value
  void     *data;    // value
};

struct Condition {
  RelAttr lhsAttr;      // left-hand side attribute
  CompOp  op;           // comparison operator

  CondType flag;
    // COND_NORMAL : normal
    // COND_ISNULL : 'lhsAttr is null'
    // COND_NOTNULL: 'lhsAttr is not null'
    // COND_LIKE   : 'lhsAttr like 'pattern''
    // COND_NOTLIKE: 'lhsAttr not like 'pattern''

  int     bRhsIsAttr;   // TRUE if right-hand side is an attribute
                        //   and not a value
  RelAttr rhsAttr;      // right-hand side attribute if bRhsIsAttr = TRUE
  Value   rhsValue;     // right-hand side value if bRhsIsAttr = FALSE

  std::string  pattern;
  bool    skip;         // used in Selector
};
const int IsNull = 1;
const int IsNotNull = 2;

struct RelationMeta{
    char relName[MAXNAME+1];//	relation name
    int tupleLength;//	tuple length in bytes
    int attrCount;//	number of attributes
    int indexCount;//	number of indexed attributes
};

/**
 * Compare two value
 * @param a
 * @param b
 * @param compOp
 * @param attrType
 * @return
 */
bool Cmp(void *a, void *b, CompOp compOp, AttrType attrType);

/**
 * Sum Up Two value
 * @param a
 * @param b
 * @param attrType
 * @return error code
 */
RC Tadd(void *a, void *b, AttrType attrType);

/**
 * Min operation
 * @param a
 * @param b
 * @param attrType
 * @return error code
 */
RC Tmin(void *a, void *b, AttrType attrType);

/**
 * Max operation
 * @param a
 * @param b
 * @param attrType
 * @return error code
 */
RC Tmax(void *a, void *b, AttrType attrType);

/**
 * Assign b to a
 * @param a
 * @param b
 * @param attrType
 * @return error code
 */
RC Tassign(void *a, void *b, AttrType attrType);

std::string relToFileName(const char *relName);

#include "RM/rm.h"
#include "PF/pf.h"

#endif //YOURSQL_YOURSQL_H

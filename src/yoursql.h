//
// Created by 杨乐 on 2018/11/5.
//

#ifndef YOURSQL_YOURSQL_H
#define YOURSQL_YOURSQL_H

#include <cassert>
#include <stdint.h>
#include <climits>
#include <float.h>

using RC = int;

const int MAXNAME = 24;

enum AttrType {INT, FLOAT, STRING, VARCHR, ERRTYPE, NULLTYPE};
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
    int      flag;
};

struct RelAttr {
  char *relName;     // relation name (may be NULL) 
  char *attrName;    // attribute name              
};

struct Value {
  AttrType type;     // type of value               
  void     *data;    // value                       
};

struct Condition {
  RelAttr lhsAttr;      // left-hand side attribute                     
  CompOp  op;           // comparison operator
  int 	  flag;			// 0 if normal; 1 if is null; 2 if is not null
  int     bRhsIsAttr;   // TRUE if right-hand side is an attribute
                        //   and not a value
  RelAttr rhsAttr;      // right-hand side attribute if bRhsIsAttr = TRUE
  Value   rhsValue;     // right-hand side value if bRhsIsAttr = FALSE
};

#include "RM/rm.h"
#include "PF/pf.h"

#endif //YOURSQL_YOURSQL_H

//
// Created by 杨乐 on 2018/11/5.
//

#ifndef YOURSQL_YOURSQL_H
#define YOURSQL_YOURSQL_H

using RC = int;

enum AttrType {INT, FLOAT, STRING};
enum CompOp {EQ_OP, NE_OP, LT_OP, GT_OP, LE_OP, GE_OP, NO_OP};

// Pin Strategy Hint
enum ClientHint {
    NO_HINT                                     // default value
};

#endif //YOURSQL_YOURSQL_H

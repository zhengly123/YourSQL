//
// Created by eric on 18-12-28.
//

#include <cstring>
#include "yoursql.h"

bool Cmp(void *a, void *b, CompOp compOp, AttrType attrType)
{
    switch (compOp)
    {
        case LT_OP:
            switch (attrType)
            {
                case INT:
                    return *(int*)(a)<*(int*)(b);
                case FLOAT:
                    return *(float*)(a)<*(float*)(b);
                case STRING:
                    return strcmp((char *) (a), (char *) (b)) < 0;
            }
            assert(false);
        case GT_OP:
            return Cmp(b, a, LT_OP, attrType);
        case EQ_OP:
            return !Cmp(a, b, LT_OP, attrType)&&!Cmp(b, a, LT_OP, attrType);
        case NE_OP:
            return !Cmp(a, b, EQ_OP, attrType);
        case LE_OP:
            return !Cmp(a, b, GT_OP, attrType);
        case GE_OP:
            return !Cmp(a, b, LT_OP, attrType);
        case NO_OP:
            return true;
    }
    assert(false);
    return false;
}


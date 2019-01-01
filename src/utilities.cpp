//
// Created by eric on 18-12-28.
//

#include <cstring>
#include "yoursql.h"
#include "Regex/Regex.h"

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
                case DATETYPE:
                    return *(int*)(a)<*(int*)(b);
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
            //TODO:LIKE
        case LK_OP:
            return Match((char*)a, (char*)b);
        case UKL_OP:
            return !Match((char*)a, (char*)b);

    }
    assert(false);
    return false;
}

bool Match(char*a, char* b)
{
    Regex pattern(b);
    return pattern.match(a);
}

RC Tadd(void *a, void *b, AttrType attrType)
{
    switch(attrType)
    {
        case INT:
            *(int*)(a) += *(int*)b;
            break;
        case FLOAT:
            *(float*)(a) += *(float*)(b);
            break;
        default:
            // Error
            break;
    }

    return 0;
}

RC Tmin(void *a, void *b, AttrType attrType)
{
    if(!Cmp(b, a, LT_OP, attrType)) return 0;
    int rc = Tassign(a, b, attrType);
    if(rc) return rc;
    return 0;
}

RC Tmax(void *a, void *b, AttrType attrType)
{
    if(!Cmp(a, b, LT_OP, attrType)) return 0;
    int rc = Tassign(a, b, attrType);
    if(rc) return rc;
    return 0;
}

RC Tassign(void *a, void *b, AttrType attrType)
{
    switch(attrType)
    {
        case INT:
            *(int*)(a) = *(int*)(b); break;
        case FLOAT:
            *(float*)(a) = *(float*)(b); break;
        case STRING:
            memcpy(a, b, MAXNAME); break;
        case VARCHR:
            memcpy(a, b, MAXNAME); break;
        case DATETYPE:
            *(int*)(a) = *(int*)(b); break;
        default:
            return 1;
    }

    return 0;
}

std::string relToFileName(const char *relName)
{
    return std::string(relName)+std::string(".rel");
}

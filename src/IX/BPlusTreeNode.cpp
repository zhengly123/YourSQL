//
// Created by eric on 18-11-26.
//

#include <cstring>
#include "BPlusTreeNode.h"
#include "IX_PRIVATE.h"

//void BPlusTreeNode::setValue(int value)
//{
//    this->value=value;
//}

BPlusTreeNode::BPlusTreeNode(AttrType attrType, int attrLength,
        bool isLeaf)
        : attrType(attrType), attrLength(attrLength), isLeaf(0), n(0)
{
    memset(keys, 0, sizeof(keys));
    memset(chRIDs, 0, sizeof(chRIDs));
}

bool BPlusTreeNode::less(void *a, void *b)
{
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
}

RC BPlusTreeNode::insert(void* key, const RID &value)
{
    assert(n<M);
    if (isLeaf)
    {
        if (n < M)
        {
            memcpy(keys + (n - 1) * attrLength, key, (unsigned int) attrLength);
            chRIDs[n] = value;
            ++n;
            return 0;
        }
        else
        {
            //TODO: split the node and insert
            return IX_RID_OF_SAME_ATTR_EXCEED;
        }
    }
    else
    {
        int t=firstGeaterIndex(key);

        memmove(keys + (t + 1) * attrLength, keys + (t + 1) * attrLength, attrLength * (n - t));
        memcpy(keys + t * attrLength, key, attrLength);
        //Do not apply chRIDs with memcpy
        for (int i = n - 1; i >= t; --i)
            chRIDs[i + 1] = chRIDs[i];
        chRIDs[t]=value;
    }
    return 0;
}

bool BPlusTreeNode::overfull()
{
    return n == M+1;
}

inline int BPlusTreeNode::firstGeaterIndex(void *key)
{
    int t;
    for (t=0;t<n&&less(key,keys+t*attrLength);++t);
    return t;
}

void *BPlusTreeNode::getKey(int k)
{
    return keys+k*KEYSIZE;
}

bool BPlusTreeNode::full()
{
    return n == M;
}

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
        : attrType(attrType), attrLength(attrLength), isLeaf(isLeaf), n(0)
{
    memset(keys, 0, sizeof(keys));
    memset(chRIDs, 0, sizeof(chRIDs));
    memset(rmFlag, 0, sizeof(rmFlag));
}

//bool BPlusTreeNode::less(void *a, void *b)
//{
//    switch (attrType)
//    {
//        case INT:
//            return *(int*)(a)<*(int*)(b);
//        case FLOAT:
//            return *(float*)(a)<*(float*)(b);
//        case STRING:
//            return strcmp((char *) (a), (char *) (b)) < 0;
//    }
//    assert(false);
//}

RC BPlusTreeNode::insert(void* key, const RID &value)
{
    assert(n<=M);
    if (isLeaf)
    {
        if (n < M)
        {
            memcpy(keys + n * attrLength, key, (unsigned int) attrLength);
            chRIDs[n] = value;
            ++n;
            return 0;
        }
        else
        {
            //TODO: append the block
            return IX_RID_OF_SAME_ATTR_EXCEED;
        }
    }
    else
    {
        int t = firstGreaterIndex(key);
        assert(t>=0);
        // insert key to keys[t]
        // move keys[t,n)
        memmove(getKey(t+1), getKey(t), attrLength * (n - t));
        memcpy(keys + t * attrLength, key, attrLength);
        // move child[t,n)
        for (int i = n - 1; i >= t; --i)
            chRIDs[i + 1] = chRIDs[i];
        chRIDs[t] = value;
        n++;
    }
    return 0;
}

bool BPlusTreeNode::overfull()
{
    return n == M+1;
}

inline int BPlusTreeNode::firstGreaterIndex(void *key)
{
    int t;
    for (t = 0; t < n && IX_IndexHandle::cmp(keys + t * attrLength, key,
             LE_OP, attrType); ++t);
    return t;
}

void *BPlusTreeNode::getKey(int k)
{
    return keys + k * attrLength;
}

bool BPlusTreeNode::full()
{
    return n == M;
}

RC BPlusTreeNode::remove(void* key,const RID &value)
{
//    int k;
//    k = firstGreaterIndex(key);
//    assert(k>0);
//    //TODO: duplicate process
//    assert(IX_IndexHandle::cmp(getKey(k-1),key, EQ_OP, attrType));
//    assert(value==chRIDs[k-1]);
//    rmFlag[k - 1] = true;
//    return 0;
}

RC BPlusTreeNode::insertFirstChild(const RID &value)
{
    assert(n==0);
    chRIDs[0] = value;
    n = 1;
    return 0;
}

//bool BPlusTreeNode::equal(void *a, void *b)
//{
//    return !less(a, b) && !less(b, a);
//}

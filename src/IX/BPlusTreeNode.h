//
// Created by eric on 18-11-26.
//

#ifndef YOURSQL_BPLUSTREENODE_H
#define YOURSQL_BPLUSTREENODE_H

#include "../yoursql.h"
#include "../RM/rm.h"

const int M=5;

// This class should be trivially-copyable
class BPlusTreeNode
{
public:
    BPlusTreeNode(AttrType attrType, int attrLength, bool isLeaf, int n);

//    void init();
//    void setValue(int value);
    AttrType attrType;
    int attrLength;
    //TODO: change type of key to all three AttrType
    char keys[10*(M-1)];
    RID chRIDs[M];
    bool isLeaf;
    int n;              // number of children
    RID parent;

    RC insert(void* key,const RID &value);
    bool less(void * a, void * b);
    bool full();
    int firstGeaterIndex(void *key);
};


#endif //YOURSQL_BPLUSTREENODE_H

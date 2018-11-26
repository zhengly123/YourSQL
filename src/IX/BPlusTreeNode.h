//
// Created by eric on 18-11-26.
//

#ifndef YOURSQL_BPLUSTREENODE_H
#define YOURSQL_BPLUSTREENODE_H

#include "../yoursql.h"
#include "../RM/rm.h"

const int M=5;
// i.e. maximum length of String
const int KEYSIZE=10;
const int KEYSARRAYSIZE=(M-1)*KEYSIZE;

// This class should be trivially-copyable
class BPlusTreeNode
{
public:
    BPlusTreeNode(AttrType attrType, int attrLength, bool isLeaf);

//    void init();
//    void setValue(int value);
    AttrType attrType;
    int attrLength;
    //TODO: change type of key to all three AttrType
    char keys[KEYSARRAYSIZE];
    RID chRIDs[M];
    bool isLeaf;
    int n;              // number of children
    RID parent;

    RC insert(void* key,const RID &value);
    bool less(void * a, void * b);
    bool full();
    bool overfull();
    void* getKey(int k);
    int firstGeaterIndex(void *key);
};


#endif //YOURSQL_BPLUSTREENODE_H

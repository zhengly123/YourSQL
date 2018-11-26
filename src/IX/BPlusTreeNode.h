//
// Created by eric on 18-11-26.
//

#ifndef YOURSQL_BPLUSTREENODE_H
#define YOURSQL_BPLUSTREENODE_H

#include "../yoursql.h"
#include "../RM/rm.h"
#include "IX_PRIVATE.h"


// This class should be trivially-copyable
class BPlusTreeNode
{
public:
    BPlusTreeNode(AttrType attrType, int attrLength, bool isLeaf);

//    void init();
//    void setValue(int value);
    AttrType attrType;
    int attrLength;
    // To support different attrType, char array is used to store keys
    char keys[KEYSARRAYSIZE];
    bool rmFlag[M];
    RID chRIDs[M];
    bool isLeaf;
    int n;              // number of children
    RID parent, succ;

    RC insert(void* key,const RID &value);
    RC remove(void* key,const RID &value);
    bool less(void * a, void * b);
    bool equal(void *a, void *b);
    bool full();
    bool overfull();
    void* getKey(int k);
    int firstGreaterIndex(void *key);
};


#endif //YOURSQL_BPLUSTREENODE_H

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
    char keys[KEYS_ARRAY_SIZE];
    bool rmFlag[M+1];
    RID chRIDs[M+1];
    bool isLeaf;
    int n;              // number of children
//    RID parent;
    // if this is a leaf node, than it should have successor
    RID nextInList;

    RC insert(void* key,const RID &value);
    RC insertFirstChild(const RID &value);
    RC remove(void* key,const RID &value);
//    bool less(void * a, void * b);
//    bool equal(void *a, void *b);
    bool full();
    bool overfull();
    void* getKey(int k);
    /**
     *
     * @param key
     * @return The index of first key greater than given key.
     */
    int firstGreaterIndex(void *key);
};


#endif //YOURSQL_BPLUSTREENODE_H

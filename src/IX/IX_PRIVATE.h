//
// Created by eric on 18-11-26.
//

#pragma once
#ifndef YOURSQL_IX_PRIVATE_H
#define YOURSQL_IX_PRIVATE_H

#include "../yoursql.h"
#include "IX_PUBLIC.h"

// M of B+ Tree. The maximum number of children which should be
// the maximum number of keys + 1.
const int M=5;
const int MAX_NUM_KEY=M-1;
const int MAX_NUM_CHILDREN=M;
// i.e. maximum length of String
const int KEY_SIZE=10;
const int KEYS_ARRAY_SIZE=(M+1)*KEY_SIZE;

class BPlusTreeNode;
class IX_Manager;
class IX_IndexHandle;
class IX_IndexScan;

struct IX_Header
{
    int pageNum;
    int pageSize;
    int rootPage;
    int indexPairSize;  //size of every index pair (attr,RIC)
    AttrType attrType;
    int attrLength;
    int cntNode;
};
//struct IX_
#include "IX_Manager.h"
#include "IX_IndexHandle.h"
#include "IX_IndexScan.h"

#endif //YOURSQL_IX_PRIVATE_H

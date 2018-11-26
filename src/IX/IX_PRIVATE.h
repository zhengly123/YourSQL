//
// Created by eric on 18-11-26.
//

#pragma once
#ifndef YOURSQL_IX_PRIVATE_H
#define YOURSQL_IX_PRIVATE_H

#include "../yoursql.h"
#include "IX_PUBLIC.h"

// M of B+ Tree
const int M=5;
// i.e. maximum length of String
const int KEYSIZE=10;
const int KEYSARRAYSIZE=(M-1)*KEYSIZE;

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
};
//struct IX_
#include "IX_Manager.h"
#include "IX_IndexHandle.h"
#include "IX_IndexScan.h"

#endif //YOURSQL_IX_PRIVATE_H

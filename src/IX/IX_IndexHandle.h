//
// Created by eric on 18-11-26.
//

#pragma once
#ifndef YOURSQL_IX_INDEXHANDLE_H
#define YOURSQL_IX_INDEXHANDLE_H

#include "../RM/rm.h"
#include "IX_PRIVATE.h"
#include "BPlusTreeNode.h"

class IX_IndexHandle {
public:
    IX_IndexHandle  ();                             // Constructor
    ~IX_IndexHandle ();                             // Destructor
    RC InsertEntry     (void *pData, const RID &rid);  // Insert new index entry
    RC DeleteEntry     (void *pData, const RID &rid);  // Delete index entry
    RC ForcePages      ();                             // Copy index to disk

    IX_IndexHandle(FileManager &fm,
            BufPageManager &bpm,
            IX_Manager &ixManager,
            IX_Header &ixHeader);

    RC open (FileManager &fm,
             BufPageManager &bpm,
             IX_Manager &ixManager,
             int fileID);

    void getFileID(int &fileID);
//    BufPageManager);

private:
    FileManager *fm;
    BufPageManager *bpm;
    IX_Manager *ixManager;
    IX_Header ixHeader;
    int fileID;

    RC createNode(PageNum &pageNum, BPlusTreeNode &node);
    RC treeInsert(int c, int p, void *pData, const RID &rid);

    // Do not change position of node in terms of  page
    RC splitChild(BPlusTreeNode *node, int ch);
};

#endif //YOURSQL_IX_INDEXHANDLE_H

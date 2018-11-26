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
    PageNum path[1000];
    int pathChild[1000];

    RC createNode(PageNum &pageNum, BPlusTreeNode &node);
    RC treeInsert(int c, int dep, void *pData, const RID &rid);
    // 需要处理pathChild的变化
    RC treeInsertUp(int c, int dep, void *pData, const RID &rid, PageNum newChild);
    RC getMinimalIndex()

    /**
     * Do not change position of node in terms of page
     * @param node
     * @param ch
     * @param subroot  allocated pageNum of the new subroot
     * @return
     */
//    RC splitChild(BPlusTreeNode *node, int ch, PageNum &subroot);
    // split should keep node pageNum the same
    RC split(int depth);

    RC copyKey(BPlusTreeNode *dst, int x1, BPlusTreeNode *src, int x2);
};

#endif //YOURSQL_IX_INDEXHANDLE_H

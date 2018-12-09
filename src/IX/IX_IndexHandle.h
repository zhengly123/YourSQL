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
    RC InsertEntry     (void *key, const RID &value);  // Insert new index entry
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

    void printBPT();
    void printLinearLeaves();

    RC next(RID &iterator, RID &dataRID, void *key) const;

    void getFileID(int &fileID);

    RC getMinimalIndex(RID &rid) const;

    bool cmp(void *a, void *b, CompOp compOp) const;
    static bool cmp(void *a, void *b, CompOp compOp, AttrType attrType);
//    BufPageManager);

private:
    FileManager *fm;
    BufPageManager *bpm;
    IX_Manager *ixManager;
    IX_Header ixHeader;
    int fileID;
    PageNum path[1000];
    int pathChild[1000];


    /**
     * Create a node in current page file. And increase pageNum.
     * @param pageNum This is a return value which shows the new allocated slotnum.
     *                Do not use header slot number directly (for slot pool).
     * @param node
     * @return
     */
    RC createNode(PageNum &pageNum, BPlusTreeNode &node);

    /**
     * Find place, insert. And split from bottom to up.
     * @param c
     * @param dep
     * @param key
     * @param value
     * @return
     */
    RC treeInsert(int c, int dep, void *key, const RID &value);
    /**
     * Split the child node and insert index to parent.
     * @param parentNode
     * @param childNode
     * @return
     */
    RC splitChild(BPlusTreeNode *parentNode, BPlusTreeNode *childNode, RID childRID);
    /**
     * Leaves for duplicate keys form a list instead of B+ tree.
     * TODO: realize UNLIMITED_DUPLICATE_KEY
     * @param node
     * @param key
     * @param value
     * @return
     */
    RC insertIntoLeaves(BPlusTreeNode *node,void *key, const RID &value);

    RC getLeftestLeaf(RID &rid);

    RID getLeftestLeafDFS(RID rid);


    RC copyKey(BPlusTreeNode *dst, int x1, BPlusTreeNode *src, int x2);

    void printDFS(const RID rid, int intend);

    void setMinimum(void *p, AttrType attrType)
    {
        switch (attrType)
        {
            case AttrType::INT :
                *((int *)p)=INT32_MIN;
                break;
            case AttrType::FLOAT :
                *((float *) p) = FLT_MIN;
                break;
            case AttrType::STRING :
                *((char *) p) = 0;
                break;
        }
    }
};

#endif //YOURSQL_IX_INDEXHANDLE_H

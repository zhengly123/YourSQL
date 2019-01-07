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
    /**
     * Depending on your design, it may require some extra effort for scans to
     * always return RIDs such that the corresponding attribute values are in
     * increasing (actually nondecreasing) order. This property is not required
     * in the project, however you may find it useful later on, e.g., if you
     * decide to use index scans to produce a sorted relation. Note that one
     * of the provided tests does exploit this property, but passing this test
     * is not required.
     * @param key
     * @param value
     * @return
     */
    RC DeleteEntry     (void *key, const RID &value);  // Delete index entry
    RC ForcePages      ();                             // Copy index to disk

    IX_IndexHandle(FileManager &fm,
            BufPageManager &bpm,
            IX_Manager &ixManager,
            IX_Header &ixHeader);

    RC open (FileManager &fm,
             BufPageManager &bpm,
             IX_Manager &ixManager,
             int fileID,
             const char *fileName, int indexNo);

    /**
     * copy index header back to bpm, flush all thing and disable handler
     * @return
     */
    RC close();

    void printBPT() const;

    void printLinearLeaves() const;

    RC nextValidEntry(RID &iterator, RID &dataRID, void *key) const;

    void getFileID(int &fileID);

    /**
     *
     * @param rid
     * @return RID of the leftest leaf. Only pageNum is valid, slotNum=0.
     */
    RC getLeftestLeaf(RID &rid) const;

    RC searchKey(char *key, RID &rid) const;

    RC getMinimalIndex(RID &rid) const;

    bool cmp(void *a, void *b, CompOp compOp) const;
    static bool cmp(void *a, void *b, CompOp compOp, AttrType attrType);
    int getAttrLength() const;
//    BufPageManager);
    string getFileName(){ return fileName;}
    int getIndexNo(){return indexNo;}
    int getCntNode(){ return ixHeader.cntNode; }

private:
    bool isOpen;
    FileManager *fm;
    BufPageManager *bpm;
    IX_Manager *ixManager;
    IX_Header ixHeader;
    BufType headBuffer;
    int fileID, headerBpmIndex;
    PageNum path[1000];
    int pathChild[1000];

    string fileName;
    int indexNo;


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

    RID getLeftestLeafDFS(RID rid) const;

    /**
     * Find the node whose key equals to provided key or the first one larger
     * then it.
     * @param key
     * @param rid
     * @return RID of the target tuple in table.
     */
    RID searchKeyDFS(char *key, RID rid) const;


    RC copyKey(BPlusTreeNode *dst, int x1, BPlusTreeNode *src, int x2);

    void printDFS(const RID rid, int intend) const;

    void setMinimum(void *p, AttrType attrType)
    {
        //TODO: add type
        switch (attrType)
        {
            case AttrType::INT :
                *((int *)p)=INT32_MIN;
                break;
            case AttrType::FLOAT :
//                *((float *) p) = FLT_MIN;
                *((float *) p) = -3.4028e+038f;
                break;
            case AttrType::STRING :
            case AttrType::VARCHR:
                *((char *) p) = 0;
                break;
            case AttrType::DATETYPE:
                *((int *) p) = 0x80000000;
                break;
            case AttrType::NULLTYPE:
            case AttrType::ERRTYPE:
                assert(0);
                break;
        }
    }
};

#endif //YOURSQL_IX_INDEXHANDLE_H

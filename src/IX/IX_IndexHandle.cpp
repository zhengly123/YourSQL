//
// Created by eric on 18-11-26.
//

#include <cstring>
#include <cassert>
#include "IX_IndexHandle.h"

RC IX_IndexHandle::open(FileManager &fm, BufPageManager &bpm,
                        IX_Manager &ixManager, int fileID)
{
    this->fm = &fm;
    this->bpm=&bpm;
    this->ixManager=&ixManager;
    this->ixHeader=ixHeader;
    this->fileID = fileID;
    int index;
    IX_Header ixHeader;
    BufType b = bpm.getPage(fileID, 0, index);
    memcpy(&ixHeader, b, sizeof(ixHeader));
    bpm.access(index);

    // Whether create root?
//    if (ixHeader.rootPage==-1)
//    {
//
//    }

    return 0;
}

void IX_IndexHandle::getFileID(int &fileID)
{
    fileID = this->fileID;
}


RC IX_IndexHandle::InsertEntry(void *pData, const RID &rid)
{
    RC rc;
    int &root=ixHeader.rootPage;
    if (root<=0)// if there is no root node
    {
        BPlusTreeNode node(ixHeader.attrType,ixHeader.attrLength,
                           true, 0);
        node.insert(pData, rid);
        rc = createNode(root, node);
        assert(rc);
        return 0;
    }
    else
    {
        int bufferIndex;
        BPlusTreeNode *node;
        node = (BPlusTreeNode*)bpm->getPage(fileID, root, bufferIndex);
        if (node->full())// if root is full
            splitChild(node, -1);
        treeInsert(root, -1, pData, rid);
    }
    return 0;
}

RC IX_IndexHandle::createNode(PageNum &pageNum, BPlusTreeNode &node)
{
//    int bufferIndex;
//    bpm->getPage(fileID,0,bufferIndex);
    RC rc;
    rc=fm->writePage(fileID,ixHeader.pageNum,
            reinterpret_cast<BufType>(&node),0);
    assert(rc==0);
    pageNum=ixHeader.pageNum++;

    return 0;
}

RC IX_IndexHandle::treeInsert(int c, int p, void *pData, const RID &rid)
{
    RC rc;
    if (c<=0)
    {
        BPlusTreeNode node(ixHeader.attrType,ixHeader.attrLength,
                true, 0);
        node.insert(pData, rid);
        rc=createNode(c,node);
        assert(rc);
        return 0;
    }
    else
    {
        int bufferIndex, chBI;
        int childNum, childPage;
        BPlusTreeNode *node, *childNode;
        node = (BPlusTreeNode*)bpm->getPage(fileID, c, bufferIndex);
        int t;
        if (node->isLeaf)
        {
            rc=node->insert(pData, rid);
            assert(rc==0);
        } else {
            childNum = node->firstGeaterIndex(pData);
            node->chRIDs[childNum].GetPageNum(childPage);
            childNode = (BPlusTreeNode*)bpm->getPage(fileID, childPage,
                    bufferIndex);
            if (childNode->full())
            {
                rc=splitChild(node,childNum);
                assert(rc);
            }
            treeInsert(childPage, c, pData, rid);
        }
    }
    return 0;
}

RC IX_IndexHandle::splitChild(BPlusTreeNode *node, int ch)
{
    //TODO: realize this function
    return 0;
}

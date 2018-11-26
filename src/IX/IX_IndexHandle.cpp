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
                           true);
        node.insert(pData, rid);
        rc = createNode(root, node);
        assert(rc);
        return 0;
    }
    else
    {
//        int bufferIndex;
//        BPlusTreeNode *node;
//        node = (BPlusTreeNode*)bpm->getPage(fileID, root, bufferIndex);
//        if (node->full())// if root is full
//            splitChild(node, -1, );
        rc=treeInsert(root,0,pData,rid);
        return rc;
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

RC IX_IndexHandle::treeInsert(int c, int dep, void *pData, const RID &rid)
{
    assert(c>0);
    int rc, bufferIndex, childC;
    BPlusTreeNode *node;
    node = (BPlusTreeNode*)bpm->getPage(fileID, c, bufferIndex);
    path[dep] = c;
    if (node->isLeaf)
    {
        if (node->full())
            return IX_LEAF_SPLIT_UNIMPLETATED;
        node->insert(pData,rid);
        bpm->markDirty(bufferIndex);
        if (node->overfull())
        {
            rc = split(dep);
            assert(rc);
        }
    } else {// continue search
        childC = node->firstGeaterIndex(pData);
        pathChild[dep] = childC;
        rc = treeInsert(childC, dep + 1, pData, rid);
        return rc;
    }
    return 0;
}

RC IX_IndexHandle::split(int depth)
{
    const int c=path[depth];
    int rc, bufferIndex;
    BPlusTreeNode *node;
    node = (BPlusTreeNode*)bpm->getPage(fileID, c, bufferIndex);
    if (!node->overfull())
        return 0;
    assert(node->overfull());

    //TODO: 必须要区分是否是叶子节点，叶子节点新增一个插入项，非叶子节点转移一个。
    // If full, spilt it
    BPlusTreeNode y(ixHeader.attrType, ixHeader.attrLength, node->isLeaf);// new node
    int yPageNum;

    // copy right part[mid+1,M)]
    int mid=M/2;
    memcpy(y.keys, node->getKey(mid + 1), KEYSIZE * (M-mid-1));
    memcpy(y.chRIDs, node->chRIDs+mid+1, KEYSIZE * (M-mid));
    createNode(yPageNum, y);
    y.n = M - mid;
    if (pathChild[depth]>=mid)//node between depth ~ depth+1
    {
        path[depth]=yPageNum;
        pathChild[depth] -= mid;
    }
//    yPageNum=ixHeader.pageNum++;
//    fm->writePage(fileID, yPageNum, (unsigned int*)&y, 0);

    if (depth==0)// root split
    {
        BPlusTreeNode r(ixHeader.attrType, ixHeader.attrLength, false);// new root
        char midKey[KEYSIZE];
        memcpy(midKey, node->getKey(M / 2), KEYSIZE);
        memset(node->getKey(M / 2), 0, KEYSIZE);
        node->n--;
        node->isLeaf=true;
        for (int j = M / 2 + 1; j < M - 1; ++j)
        {
            // start index of y
            int i = j - (M / 2 + 1);
            copyKey(&y, i, node, j);
//            y.chRIDs[i] = node->chRIDs[j];
//            y.n++;
            node->chRIDs[i].Set(0, 0);
            node->n--;
        }
        for (int i = 0; i < M; ++i)
        {
            node->chRIDs[i].Set(0, 0);
        }
        PageNum pageNum;
        createNode(pageNum, y);

        memcpy(r.getKey(0), midKey, KEYSIZE);
        r.chRIDs[0].Set(c, 0);
        r.chRIDs[1].Set(pageNum, 0);

        createNode(pageNum, r);
        ixHeader.rootPage=pageNum;
    } else {// non-root split
        if (node->isLeaf)
        {
            //TODO
            return IX_LEAF_SPLIT_UNIMPLETATED;
        }
        else
        {
            rc = treeInsertUp(path[depth - 1], depth, node->getKey(mid),
                              node->chRIDs[mid],yPageNum);
            assert(rc);
            node->n = mid - 1;
        }
    }
    return 0;
}

RC IX_IndexHandle::treeInsertUp(int c, int dep, void *pData, const RID &rid, PageNum newChild)
{
    int bufferIndex;
    BPlusTreeNode *node;
    node = (BPlusTreeNode*)bpm->getPage(fileID, c, bufferIndex);
    if (node->overfull())
        split(dep-1);
    assert(!node->overfull());

    return 0;
}

//RC IX_IndexHandle::treeInsert(int c, int p, void *pData, const RID &rid)
//{
//    RC rc;
//    if (c<=0)
//    {
//        BPlusTreeNode node(ixHeader.attrType,ixHeader.attrLength, true);
//        node.insert(pData, rid);
//        rc=createNode(c,node);
//        assert(rc);
//        return 0;
//    }
//    else
//    {
//        int bufferIndex, chBI;
//        int childNum, childPage;
//        BPlusTreeNode *node, *childNode;
//        node = (BPlusTreeNode*)bpm->getPage(fileID, c, bufferIndex);
//        int t;
//        if (node->isLeaf)
//        {
//            rc=node->insert(pData, rid);
//            assert(rc==0);
//        } else {
//            childNum = node->firstGeaterIndex(pData);
//            node->chRIDs[childNum].GetPageNum(childPage);
//            childNode = (BPlusTreeNode*)bpm->getPage(fileID, childPage,
//                    bufferIndex);
//            if (childNode->full())
//            {
//                rc = splitChild(node, childNum);
//                assert(rc);
//            }
//            treeInsert(childPage, c, pData, rid);
//        }
//    }
//    return 0;
//}

//RC IX_IndexHandle::splitChild(BPlusTreeNode *node, int ch, PageNum &subroot)
//{
//    //TODO: realize this function
//    BPlusTreeNode *node1, *node3=new BPlusTreeNode(ixHeader.attrType,
//            ixHeader.attrLength, true);
//    if (ch == -1)//This can only append on the root node
//    {
//        char midKey[KEYSIZE];
//        memcpy(midKey, node->getKey(M / 2), KEYSIZE);
//        memset(node->getKey(M / 2), 0, KEYSIZE);
//        node->n--;
//        node1 = new BPlusTreeNode(ixHeader.attrType, ixHeader.attrLength,
//                                  false);
//        node->isLeaf=true;
//        for (int j = M / 2 + 1; j < M - 1; ++j)
//        {
//            // start index of node3
//            int i = j - (M / 2 + 1);
//            copyKey(node3, i, node, j);
//            node3->chRIDs[i] = node->chRIDs[j];
//            node3->n++;
//            node->chRIDs[i].Set(0, 0);
//            node->n--;
//        }
//        for (int i = 0; i < M; ++i)
//        {
//            node->chRIDs[i].Set(0, 0);
//        }
//        PageNum pageNum;
//        createNode(pageNum, *node3);
//
//        memcpy(node1->getKey(0), midKey, KEYSIZE);
//        node1->chRIDs[0].Set(ch, 0);
//        node1->chRIDs[1].Set(pageNum, 0);
//
//        createNode(pageNum, *node1);
//        ixHeader.rootPage=pageNum;
//    } else {
//
//    }
//    return 0;
//}

RC IX_IndexHandle::copyKey(BPlusTreeNode *dst, int x1,
        BPlusTreeNode *src, int x2)
{
    memcpy(dst->keys + x1 * ixHeader.attrLength,
           src->keys + x2 * ixHeader.attrLength, ixHeader.attrLength);
    return 0;
}

RC IX_IndexHandle::DeleteEntry(void *pData, const RID &rid)
{

    return 0;
}

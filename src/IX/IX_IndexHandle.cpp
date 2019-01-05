//
// Created by eric on 18-11-26.
//

#include <cstring>
#include <cassert>
#include "IX_IndexHandle.h"

RC IX_IndexHandle::open(FileManager &fm, BufPageManager &bpm,
                        IX_Manager &ixManager, int fileID, const char *fileName, int indexNo)
{
    this->fm = &fm;
    this->bpm=&bpm;
    this->ixManager=&ixManager;
    this->fileID = fileID;
    this->fileName = string(fileName);
    this->indexNo = indexNo;
    this->isOpen = true;
    headBuffer = bpm.getPage(fileID, 0, headerBpmIndex);
    memcpy(&this->ixHeader, headBuffer, sizeof(this->ixHeader));
    bpm.access(headerBpmIndex);
    bpm.markDirty(headerBpmIndex);
    return 0;
}

void IX_IndexHandle::getFileID(int &fileID)
{
    fileID = this->fileID;
}


RC IX_IndexHandle::InsertEntry(void *key, const RID &value)
{
    RC rc;
    int &rootPage=ixHeader.rootPage;
    if (rootPage<=0)// if there is no rootPage node
    {
        char minKey[KEY_SIZE];
        int leafPage;
        setMinimum(minKey, ixHeader.attrType);
        // create a tree with minimal key
        BPlusTreeNode node(ixHeader.attrType, ixHeader.attrLength, false);
        BPlusTreeNode leafNode(ixHeader.attrType, ixHeader.attrLength, true);

        rc = createNode(leafPage, leafNode);
        assert(rc==0);

        node.insert(minKey, RID(leafPage,0));
        rc = createNode(rootPage, node);
//        return 0;
    }
//    else
//    {
        int bufferIndex, childK;
        BPlusTreeNode *rootNode;

        rc=treeInsert(rootPage,0,key,value);
        rootNode = (BPlusTreeNode*)bpm->getPage(fileID, rootPage, bufferIndex);
        bpm->markDirty(bufferIndex);
        if (rootNode->overfull())
        {
            BPlusTreeNode newRootNode(ixHeader.attrType, ixHeader.attrLength, false);// new node
            int newRootPageNum;
            newRootNode.insert(rootNode->getKey(0),RID(rootPage, 0));
            splitChild(&newRootNode, rootNode, RID(0,0));
            createNode(newRootPageNum, newRootNode);
            rootPage = newRootPageNum;
        }
        return rc;
}

RC IX_IndexHandle::createNode(PageNum &pageNum, BPlusTreeNode &node)
{
    RC rc;
    rc=fm->writePage(fileID,ixHeader.pageNum,
            reinterpret_cast<BufType>(&node),0);
    assert(rc==0);
    pageNum=ixHeader.pageNum++;

    return 0;
}

RC IX_IndexHandle::treeInsert(int c, int dep, void *key, const RID &value)
{
    assert(c>0);
    int rc, bufferIndex, childK;
    BPlusTreeNode *node;
    node = (BPlusTreeNode*)bpm->getPage(fileID, c, bufferIndex);
    bpm->markDirty(bufferIndex);
//    path[dep] = c;
    if (node->isLeaf)
    {
        assert((rc=insertIntoLeaves(node,key,value))==0);
    } else {// continue search
        childK = node->firstGreaterIndex(key) - 1;
        assert(childK>=0);// there is no deletion
//        pathChild[dep] = childK;
        int childPage=node->chRIDs[childK].GetPageNum();
        int childBufferIndex;
        BPlusTreeNode *childNode;

        childNode = (BPlusTreeNode*)bpm->getPage(fileID, childPage, childBufferIndex);
        bpm->markDirty(childBufferIndex);
        if (childNode->isLeaf)
        {
            if (cmp(node->getKey(childK), key, EQ_OP) == false)
            {
                //create a leaf and insert the KV pair
                int newPageNum;
                BPlusTreeNode newLeafNode(ixHeader.attrType, ixHeader.attrLength, true);

                // maintain the linked list
                int prepPage = node->chRIDs[childK].GetPageNum();
                int prepBufferIndex;
                BPlusTreeNode *prepNode = (BPlusTreeNode *) bpm->getPage(fileID,
                        prepPage, prepBufferIndex);
                bpm->markDirty(prepBufferIndex);
                newLeafNode.nextInList = prepNode->nextInList;

                createNode(newPageNum, newLeafNode);
                prepNode->nextInList = RID(newPageNum, 0);

                assert((rc = node->insert(key, RID(newPageNum, 0)))==0);

                ++childK;
                childNode = &newLeafNode;
            }
            assert(cmp(node->getKey(childK), key, EQ_OP) == 1);//DEBUG
            // children index of last level nodes above leaves is different from others
            childPage = node->chRIDs[childK].GetPageNum();
        }
        assert((rc = treeInsert(childPage, dep + 1, key, value))==0);

        // check the size of child and split
        if (childNode->n>M)
        {
            splitChild(node, childNode, node->chRIDs[childK]);
        }
    }
    return 0;
}

RC IX_IndexHandle::splitChild(BPlusTreeNode *parentNode, BPlusTreeNode *childNode, RID childRID)
{
    int rc;
    BPlusTreeNode newNode(ixHeader.attrType, ixHeader.attrLength, false);// new node
    int newPageNum;

    assert(childNode->overfull());//DEBUG n=M+1
    // copy right part[mid,M+1]
    int mid=childNode->n/2;
    newNode.n = childNode->n - mid;
    newNode.nextInList=childNode->nextInList;
    memcpy(newNode.keys, childNode->getKey(mid), ixHeader.attrLength * (newNode.n));
    memcpy(newNode.chRIDs, childNode->chRIDs + mid, sizeof(RID) * (newNode.n));
    createNode(newPageNum, newNode);

    // get page number after new node is allocated
    childNode->nextInList = RID(newPageNum, 0);
    childNode->n = mid;

    // insert to parent node
    assert((rc=parentNode->insert(newNode.getKey(0), RID(newPageNum, 0)))==0);
}

//RC IX_IndexHandle::insertIntoLeaves(BPlusTreeNode *node,void *key, const RID &value)
//RC IX_IndexHandle::split(int depth)
//{
//    const int c=path[depth];
//    int rc, bufferIndex;
//    BPlusTreeNode *node;
//    node = (BPlusTreeNode*)bpm->getPage(fileID, c, bufferIndex);
//    if (!node->overfull())
//        return 0;
//    assert(node->overfull());
//
//    //TODO: 必须要区分是否是叶子节点，叶子节点新增一个插入项，非叶子节点转移一个。
//    // If full, spilt it
//    BPlusTreeNode y(ixHeader.attrType, ixHeader.attrLength, node->isLeaf);// new node
//    int yPageNum;
//
//    // copy right part[mid+1,M)]
//    int mid=M/2;
//    memcpy(y.keys, node->getKey(mid + 1), KEY_SIZE * (M-mid-1));
//    memcpy(y.chRIDs, node->chRIDs+mid+1, KEY_SIZE * (M-mid));
//    createNode(yPageNum, y);
//    y.n = M - mid;
//    if (pathChild[depth]>=mid)//node between depth ~ depth+1
//    {
//        path[depth]=yPageNum;
//        pathChild[depth] -= mid;
//    }
////    yPageNum=ixHeader.pageNum++;
////    fm->writePage(fileID, yPageNum, (unsigned int*)&y, 0);
//
//    if (depth==0)// root split
//    {
//        BPlusTreeNode r(ixHeader.attrType, ixHeader.attrLength, false);// new root
//        char midKey[KEY_SIZE];
//        memcpy(midKey, node->getKey(M / 2), KEY_SIZE);
//        memset(node->getKey(M / 2), 0, KEY_SIZE);
//        node->n--;
//        node->isLeaf=true;
//        for (int j = M / 2 + 1; j < M - 1; ++j)
//        {
//            // start index of y
//            int i = j - (M / 2 + 1);
//            copyKey(&y, i, node, j);
////            y.chRIDs[i] = node->chRIDs[j];
////            y.n++;
//            node->chRIDs[i].Set(0, 0);
//            node->n--;
//        }
//        for (int i = 0; i < M; ++i)
//        {
//            node->chRIDs[i].Set(0, 0);
//        }
//        PageNum pageNum;
//        createNode(pageNum, y);
//
//        memcpy(r.getKey(0), midKey, KEY_SIZE);
//        r.chRIDs[0].Set(c, 0);
//        r.chRIDs[1].Set(pageNum, 0);
//
//        createNode(pageNum, r);
//        ixHeader.rootPage=pageNum;
//    } else {// non-root split
//        if (node->isLeaf)
//        {
//            //TODO
//            return IX_LEAF_SPLIT_UNIMPLETATED;
//        }
//        else
//        {
//            rc = treeInsertUp(path[depth - 1], depth, node->getKey(mid),
//                              node->chRIDs[mid],yPageNum);
//            assert(rc);
//            node->n = mid - 1;
//        }
//    }
//    return 0;
//}

//RC IX_IndexHandle::treeInsertUp(int c, int dep, void *pData, const RID &rid, PageNum newChild)
//{
//    int bufferIndex;
//    BPlusTreeNode *node;
//    node = (BPlusTreeNode*)bpm->getPage(fileID, c, bufferIndex);
//    if (node->overfull())
//        split(dep-1);
//    assert(!node->overfull());
//
//    return 0;
//}

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
//            childNum = node->firstGreaterIndex(pData);
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
//        char midKey[KEY_SIZE];
//        memcpy(midKey, node->getKey(M / 2), KEY_SIZE);
//        memset(node->getKey(M / 2), 0, KEY_SIZE);
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
//        memcpy(node1->getKey(0), midKey, KEY_SIZE);
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

RC IX_IndexHandle::DeleteEntry(void *key, const RID &value)
{
    int rc, c, bufferIndex, k;
    BPlusTreeNode *node, *nextNode;

    c = ixHeader.rootPage;
    if (c<=0)
        return IX_NO_INDEX_EXIST;

    node = (BPlusTreeNode*)bpm->getPage(fileID, c, bufferIndex);
    bpm->markDirty(bufferIndex);
    while (!node->isLeaf)
    {
        k = node->firstGreaterIndex(key);
        if (k==0)
            return IX_NO_INDEX_EXIST;
        node->chRIDs[k-1].GetPageNum(c);
        nextNode = (BPlusTreeNode*)bpm->getPage(fileID, c, bufferIndex);
        bpm->markDirty(bufferIndex);
        if (nextNode->isLeaf && cmp(node->getKey(k-1),key,NE_OP))
            return IX_NO_INDEX_EXIST;
        node=nextNode;
    }
    assert(cmp(node->getKey(0),key,EQ_OP));
    while (node&&cmp(node->getKey(0),key,EQ_OP))
    {
        rc = node->remove(key, value);
        int nextPageNum = node->nextInList.GetPageNum();
        if (!nextPageNum)
            break;
        node = (BPlusTreeNode *) bpm->getPage(fileID, nextPageNum, bufferIndex);
        bpm->markDirty(bufferIndex);
    }
    return rc;
}

RC IX_IndexHandle::ForcePages()
{
//    memcpy(headBuffer, &this->ixHeader, sizeof(this->ixHeader));
//    bpm->markDirty(headerBpmIndex);
//    bpm->close(fileID);
    return 0;
}

RC IX_IndexHandle::getMinimalIndex(RID &rid) const
{
    int rc, c, bufferIndex;
    BPlusTreeNode *node;

    c = ixHeader.rootPage;
    if (c<=0)
        return IX_NO_INDEX_EXIST;

    node = (BPlusTreeNode*)bpm->getPage(fileID, c, bufferIndex);
    while (!node->isLeaf)
    {
        node->chRIDs[0].GetPageNum(c);
        node = (BPlusTreeNode*)bpm->getPage(fileID, c, bufferIndex);
    }
    rid.Set(c,0);
    return 0;
}

RC IX_IndexHandle::nextValidEntry(RID &scanRID, RID &dataRID, void *key) const
{
    BPlusTreeNode *node;
    int bufferIndex;

    node = (BPlusTreeNode*)bpm->getPage(fileID, scanRID.GetPageNum(),
            bufferIndex);
    do
    {
        if (scanRID.GetSlotNum() + 1 < node->n)
        {
            scanRID.SetSlotNum(scanRID.GetSlotNum()+1);
        } else {
            scanRID.Set(node->nextInList.GetPageNum(),0);
            node = (BPlusTreeNode*)bpm->getPage(fileID, scanRID.GetPageNum(),
                                                bufferIndex);
        }
        if (scanRID.GetPageNum()<=0)
        {
            return IX_ITERATOR_TO_END;
        }
    } while(node->rmFlag[scanRID.GetSlotNum()]);
    dataRID = node->chRIDs[scanRID.GetSlotNum()];
    memcpy(key, node->getKey(scanRID.GetSlotNum()), ixHeader.attrLength);
    return 0;
}

bool IX_IndexHandle::cmp(void *a, void *b, CompOp compOp) const
{
    return IX_IndexHandle::cmp(a, b, compOp, ixHeader.attrType);
}

bool IX_IndexHandle::cmp(void *a, void *b, CompOp compOp, AttrType attrType)
{
//    switch (compOp)
//    {
//        case LT_OP:
//            switch (attrType)
//            {
//                case INT:
//                    return *(int*)(a)<*(int*)(b);
//                case FLOAT:
//                    return *(float*)(a)<*(float*)(b);
//                case STRING:
//                    return strcmp((char *) (a), (char *) (b)) < 0;
//            }
//            assert(false);
//        case GT_OP:
//            return cmp(b, a, LT_OP, attrType);
//        case EQ_OP:
//            return !cmp(a, b, LT_OP, attrType)&&!cmp(b, a, LT_OP, attrType);
//        case NE_OP:
//            return !cmp(a, b, EQ_OP, attrType);
//        case LE_OP:
//            return !cmp(a, b, GT_OP, attrType);
//        case GE_OP:
//            return !cmp(a, b, LT_OP, attrType);
//        case NO_OP:
//            return true;
//    }
//    assert(false);
//    return false;
    return Cmp(a, b, compOp, attrType);
}

RC IX_IndexHandle::insertIntoLeaves(BPlusTreeNode *node, void *key, const RID &value)
{
    BPlusTreeNode *curNode=node, *nextNode;
    int nextBufferIndex;
    // if leaf node is full, then use linked list to extend it
    while (curNode->n==M)
    {
        if (curNode->nextInList.GetPageNum() == 0)
            break;
        nextNode = (BPlusTreeNode *) bpm->getPage(fileID, curNode->nextInList.GetPageNum(),
                                                  nextBufferIndex);
        bpm->markDirty(nextBufferIndex);
        assert(nextNode->n);
        if (cmp(nextNode->getKey(0),key,NE_OP))
            break;
        curNode=nextNode;
    }
    assert(curNode->n<=M);
    if (curNode->n==M)
    {
        BPlusTreeNode newNode(ixHeader.attrType, ixHeader.attrLength, true);// new node
        int newPageNum;
        newNode.nextInList=curNode->nextInList;
        newNode.insert(key, value);
        createNode(newPageNum, newNode);
        curNode->nextInList = RID(newPageNum, 0);
    }
    else
        curNode->insert(key, value);
    return 0;
}

void IX_IndexHandle::printBPT()
{
    RC rc;
    int &root=ixHeader.rootPage;
    if (root<=0)// if there is no root node
    {
        printf("No root.\n");
    }
    else
    {
        printDFS(RID(root, 0), 1);
    }
    fflush(stdout);
}

void IX_IndexHandle::printDFS(const RID rid, int intend)
{
    for (int i = 0; i < intend; ++i)
        printf("  ");

    int rc, bufferIndex, childK;
    BPlusTreeNode *node = (BPlusTreeNode *) bpm->getPage(fileID, rid.GetPageNum(), bufferIndex);

    printf("isleaf=%d;next=%d;rid=(%d,%d)||", node->isLeaf, node->nextInList.GetPageNum(), rid.GetPageNum(), rid.GetSlotNum());
    for (int i=0;i<node->n;++i)
    {
        printf("(%d,%d;%d)",node->chRIDs[i].GetPageNum(),node->chRIDs[i].GetSlotNum(),
               *((int *)node->getKey(i)));
    }
    puts("");
//    printf("(%d)\n",node->chRIDs[node->n].GetPageNum());
    if (node->isLeaf == false)
    {
        for (int i = 0; i < node->n; ++i)
        {
            printDFS(node->chRIDs[i],intend+1);
        }
    }
}

IX_IndexHandle::IX_IndexHandle(): isOpen(false)
{

}

IX_IndexHandle::~IX_IndexHandle()
{
    if (isOpen)
        close();
}

void IX_IndexHandle::printLinearLeaves()
{
    RID rid;
    getLeftestLeaf(rid);
    int rc, bufferIndex;
    BPlusTreeNode *node;
    puts("=========Linear output===========");
    while (rid.GetPageNum()!=0)
    {
        node = (BPlusTreeNode*)bpm->getPage(fileID, rid.GetPageNum(), bufferIndex);
        for (int i = 0; i < node->n; ++i)
            if (!node->rmFlag[i])
                printf("(%d,%d;%d,del=%d)->",node->chRIDs[i].GetPageNum(),node->chRIDs[i].GetSlotNum(),
                       *((int *)node->getKey(i)), node->rmFlag[i]);
        rid=node->nextInList;
    }
    puts("");
}

RC IX_IndexHandle::getLeftestLeaf(RID &rid) const
{
    int root=ixHeader.rootPage;
    if (root<=0)// if there is no root node
    {
        printf("No root.\n");
        return IX_EMPTY_TREE;
    }
    rid= getLeftestLeafDFS(RID(root,0));
    return 0;
}

RID IX_IndexHandle::getLeftestLeafDFS(RID rid) const
{
    int c=rid.GetPageNum();
    assert(c>0);
    int rc, bufferIndex, childK;
    BPlusTreeNode *node;
    node = (BPlusTreeNode*)bpm->getPage(fileID, c, bufferIndex);
    bpm->markDirty(bufferIndex);
    if (node->isLeaf)
        return rid;
    return getLeftestLeafDFS(node->chRIDs[0]);
}

int IX_IndexHandle::getAttrLength() const
{
    return ixHeader.attrLength;
}

RC IX_IndexHandle::close()
{
    assert(isOpen);
    BufType headerNewBuf;
    int headerNewIndex;
    headerNewBuf = bpm->getPage(fileID, 0, headerNewIndex);
    memcpy(headerNewBuf, &this->ixHeader, sizeof(this->ixHeader));
    bpm->markDirty(headerNewIndex);
    this->fileID = -1;
    this->fileName = "";
    this->indexNo = -1;
    this->isOpen = false;
    return 0;
}


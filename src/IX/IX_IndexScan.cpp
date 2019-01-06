//
// Created by eric on 18-11-26.
//

#include <cstring>
#include "IX_IndexScan.h"

IX_IndexScan::IX_IndexScan()
{

}

IX_IndexScan::~IX_IndexScan()
{

}

RC IX_IndexScan::OpenScan(const IX_IndexHandle &indexHandle, CompOp compOp,
        void *value, ClientHint pinHint)
{
    int rc;
    this->indexHandle = &indexHandle;
    // If compOp can be speeded up by choose from middle
    indexHandle.printBPT();
    if (compOp == CompOp::EQ_OP || compOp == CompOp::GE_OP
        || compOp == CompOp::GT_OP)
        rc = indexHandle.searchKey((char *) value, scanRID);
    else
        rc = indexHandle.getLeftestLeaf(scanRID);
    assert(rc==0);
    int a, b;
    scanRID.GetPageNum(a);
    scanRID.GetSlotNum(b);
    scanRID.Set(a, b - 1);
    this->compOp = compOp;
    memcpy(targetValue, value, indexHandle.getAttrLength());
    return 0;
}

RC IX_IndexScan::CloseScan()
{
    indexHandle = nullptr;
    scanRID.Set(-1, -1);
    return 0;
}

RC IX_IndexScan::GetNextEntry(RID &rid)
{
    int rc;
    //TODO: get page and search
    RID dataRID;
    char key[KEY_SIZE];
    rc = indexHandle->nextValidEntry(scanRID, dataRID, key);
    if (rc == IX_ITERATOR_TO_END)
    {
//        puts("IndexScan WARNING");
        return rc;
    }
    assert(rc==0);
    // Check whether the value meet the condition
    while (!indexHandle->cmp(key, targetValue, compOp))
    {
        // if scanRID leave the left part of axis, pruning it
        if ((compOp == CompOp::EQ_OP || compOp == CompOp::LT_OP ||
             compOp == CompOp::LE_OP) && indexHandle->cmp(key, targetValue, CompOp::GT_OP))
        {
            return IX_ITERATOR_TO_END;
        }

        rc = indexHandle->nextValidEntry(scanRID, dataRID, key);
        assert(rc >= 0);
        if (rc == IX_ITERATOR_TO_END)
        {
//            puts("IndexScan WARNING");
            return rc;
        }
        assert(rc==0);
    }
    rid=dataRID;
//    printf("scanRID:%d,%d\n", scanRID.GetPageNum(), scanRID.GetSlotNum());
    return 0;
}

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
//    rc=indexHandle.getMinimalIndex(scanRID);
    rc=indexHandle.getLeftestLeaf(scanRID);
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
    while (!indexHandle->cmp(targetValue, key, compOp))
    {
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

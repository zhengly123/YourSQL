//
// Created by eric on 18-11-26.
//

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
    rc=indexHandle.getMinimalIndex(iterator);
    assert(rc);
    int a, b;
    iterator.GetPageNum(a);
    iterator.GetSlotNum(b);
    iterator.Set(a, b - 1);
    this->compOp = compOp;
    return 0;
}

RC IX_IndexScan::CloseScan()
{
    indexHandle = nullptr;
    iterator.Set(-1, -1);
    return 0;
}

RC IX_IndexScan::GetNextEntry(RID &rid)
{
    int rc, start = rid.GetSlotNum() + 1;
    //TODO: get page and search
    RID dataRID;
    char key[KEYSIZE];
    indexHandle->next(iterator, dataRID, key);
    while (indexHandle->cmp(targetValue, key, compOp))
    {
        rc = indexHandle->next(iterator, dataRID, key);
        assert(rc >= 0);
        if (rc > 0)
        {

            return rc;
        }
    }
    rid=dataRID;
    return 0;
}

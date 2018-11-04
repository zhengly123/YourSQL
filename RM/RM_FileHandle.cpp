//
// Created by 杨乐 on 2018/11/4.
//

#include "rm.h"
#include "../PF/bufmanager/BufPageManager.h"
#include "../PF/fileio/FileManager.h"

/*
 * Constructor
 */
RM_FileHandle :: RM_FileHandle  ()
{

}

/*
 * Destructor
 */
RM_FileHandle :: ~RM_FileHandle ()
{

}

/*
 * Set file ID
 */
RC RM_FileHandle :: SetID          (int id)
{
    this->fileID = id;
    return 0;
}

/*
 * Get file ID
 */
RC RM_FileHandle :: GetID          (int &id)
{
    id = this->fileID;
    return 0;
}

/*
 * Set RM_Manager
 */
RC RM_FileHandle :: SetRmm         (RM_Manager *rmm)
{
    this.rmm = rmm;
    return 0;
}

/*
 * Set RecordSize
 */
RC RM_FileHandle :: SetRecordSize  (int RecordSize)
{
    this->recordSize = recordSize;
    return 0;
}

/*
 * Get a record
 */
RC RM_FileHandle :: GetRec         (const RID &rid, RM_Record &rec) const
{
    int pageNum, slotNum;
    rid.GetPageNum(pageNum);
    rid.GetSlotNum(slotNum);

    int index;
    BufType b = rmm->bpm->getPage(this->fileID, pageNum, index);
    rmm->bpm->access(index);

    BufType b_copy;
    b_copy = (BufType)malloc(sizeof(int) * recordSize);
    memcpy(b_copy, b, sizeof(int) * recordSize); // copy the content of the record
    rec.SetData(b_copy);
    rec.SetRid(rid);

    return 0;
}

/*
 * Insert a new record, return record id
 */
RC RM_FileHandle :: InsertRec      (const char *pData, RID &rid)
{
    int pageNum, slotNum;

    int index;
    BufType b = rmm->bpm->getPage(this->fileID, 0, index);

    int totalpage = b[1]; // current page : totalpage - 1
    int totalslot = b[totalpage]; // current slot : totalslot - 1

    int maxslot = PAGE_INT_NUM / recordSize;

    if (totalslot == maxslot) // exceed the maxslot
    {
        // Page
        totalpage ++;   // increase a new page
        b[1] ++;        // update the file

        // Slot
        totalslot = 0;      // new slot
        b[totalpage] = 1;   // update the file

        rmm->bpm->markDirty(index);

    }
    else
    {
        // Slot
        b[totalpage] ++;    // update the file

        rmm->bpm->markDirty(index);
    }

    BufType bty = rmm->bpm->getPage(this->fileID, totalpage - 1, index);

    pageNum = totalpage - 1;
    slotNum = totalslot;

    rid.Set(pageNum, slotNum); // set the rid

    memcpy(bty + slotNum * recordSize, pData, sizeof(int) * recordSize); // copy data from pData

    rmm->bpm->markDirty(index);

    return 0;
}

/*
 * Delete a record
 * TODO: complete it
 */
RC RM_FileHandle :: DeleteRec      (const RID &rid)
{
    return 0;
}

/*
 * Update a record
 */
RC RM_FileHandle :: UpdateRec      (const RM_Record &rec)
{
    char* pData;
    RID rid;

    rec.GetData(pData);
    rec.GetRid(rid);

    int index;
    BufType b = rmm->bpm->getPage(this->fileID, rid.GetPageNum(), index);
    memcpy(b + rid.GetSlotNum() * recordSize, pData, sizeof(int) * recordSize); // copy data from pData
    rmm->bpm->markDirty(index);

    return 0;
}

/*
 * Write dirty page(s) to disk
 * TODO: ?
 */
RC RM_FileHandle :: ForcePages     (PageNum pageNum = ALL_PAGES) const
{

}



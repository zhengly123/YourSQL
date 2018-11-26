//
// Created by 杨乐 on 2018/11/4.
//

#include "rm_internal.h"

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
 * Set Info
 */
RC RM_FileHandle :: Set            (int id,
                   RM_Manager* rmm,
                   FileManager* fm,
                   BufPageManager* bpm,
                   int recordSize,
                   int recordPerpage)
{
    this->fileID = id;
    this->rmm = rmm;
    this->fm = fm;
    this->bpm = bpm;
    this->recordSize = recordSize;
    this->recordPerpage = recordPerpage;
    this->recordShift = (recordPerpage - 1) / 8 + 1;

    return 0;
}

/*
 * Get Info
 */

RC RM_FileHandle :: Get (int &fileID,
                     int &recordSize,
                     int &recordPerpage,
                     int &recordShift,
                     FileManager *&fm,
                     BufPageManager *&bpm) const
{
    fileID = this->fileID;
    recordSize = this->recordSize;
    recordPerpage = this->recordPerpage;
    recordShift = this->recordShift;
    fm = this->fm;
    bpm = this->bpm;

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
 * Get a record
 */
RC RM_FileHandle :: GetRec         (const RID &rid, RM_Record &rec) const
{
    if(D) cerr << "Get Record" << endl;

    int pageID, slotID;

    rid.GetPageNum(pageID);
    rid.GetSlotNum(slotID);

    int index;
    BufType b = bpm->getPage(fileID, pageID, index);
    char* brec = (char*) b + recordShift + 4 + recordSize * slotID;
    char* bcop = (char*) malloc(recordSize);
    memcpy(bcop, brec, recordSize); // copy the info

    if(D) cerr << "     Pos Offset = " << brec - (char*)b <<endl;

    bpm->access(index);

    rec.SetData(bcop);
    rec.SetRid(rid);

    return 0;
}

/*
 * Insert a new record, return record id
 */
RC RM_FileHandle :: InsertRec      (const char *pData, RID &rid)
{
    if(D) cerr << "Insert Record" << endl;

    // Get info from Page #0
    int index0;
    BufType b0 = bpm->getPage(fileID, 0, index0);

    int pageID = b0[3]; // first empty page

    if(D) cerr << "    First empty page = " << pageID << endl;

    if(!pageID) // no empty page
    {
        if(D) cerr << "    [ERROR] No empty page" << endl;

        // new a page
        b0[2] ++;
        b0[3] = pageID = b0[2];
        bpm->markDirty(index0); // modify the message in header

        if(D) cerr << "    Create a new page, pageID = " << pageID << endl;

        int indexnew;
        BufType bnew = bpm->allocPage(fileID, pageID, indexnew, false);
        memset(bnew, 0, PAGE_SIZE); // refresh the page
        bpm->markDirty(indexnew);

        if(D) cerr << "    Page Refresh."<< endl;
    }

    int indexk;
    BufType bk = bpm->getPage(fileID, pageID, indexk);

    if(D) cerr << "    Page Fetch, pageID = " <<  pageID << endl;

    int emptyCnt = 0;
    int emptySlot = 0;
    char* bitm = (char*)bk;

    for(int i = 0; i <= recordPerpage / 8; ++ i, ++ bitm)
    {
        char bitmask = *bitm;
        for(int j = i * 8; j < i * 8 + 8 && j < recordPerpage; ++ j, bitmask >>= 1)
            if(!(bitmask & 1)) if(emptyCnt ++ == 0) emptySlot = j;
    }

    if(D) cerr << "    Slot found, SlotID = " << emptySlot << endl;

    // Update bitmap
    bitm = (char*) bk + (emptySlot / 8);
    (*bitm) |= 1 << (emptySlot % 8);

    if(D) cerr << "    Bitmap updated. " << endl;

    // copy the data
    int slotID = emptySlot;
    char* retAddr = (char*)bk + recordShift + 4 + recordSize * slotID;
    memcpy(retAddr, pData, recordSize);
    if(D) cerr << "    Content copied." << endl;
    if(D) {
        //
        cerr <<  "     Src = " << *(int*)pData << endl;
        cerr <<  "     Dst = " << *(int*)retAddr << endl;
        cerr <<  "     Pos offset = " << retAddr - (char*)bk << endl;
    }

    bpm->markDirty(indexk);

    rid.Set(pageID, slotID);

    if(emptyCnt == 1) // Filled
    {
        int nxtpage = *(int*)((char*)bk + recordShift);
        bpm->access(indexk);

        b0 = bpm->getPage(fileID, 0, index0);
        b0[3] = nxtpage;
        bpm->markDirty(index0);
        if(D) cerr << "    Page Filled, Nextpage = " << nxtpage << endl;
    }

    return 0;
}

/*
 * Delete a record
 * TODO:
 */
RC RM_FileHandle :: DeleteRec      (const RID &rid)
{
    int pageID, slotID;

    rid.GetPageNum(pageID);
    rid.GetSlotNum(slotID);

    int indexk, index0;

    BufType b0 = bpm->getPage(fileID, 0, index0);
    int nxtpage = b0[3];
    b0[3] = pageID;
    bpm->markDirty(index0);

    BufType bk = bpm->getPage(fileID, pageID, indexk);

    // Update bitmap
    char* bitm = (char*) bk + (slotID / 8);
    if(((*bitm) >> (slotID % 8)) & 1)
        (*bitm) -= 1 << (slotID % 8);
    else {
        // TODO: already deleted or the record doesnt exist
    }

    // Update next empty page
    *(int*)((char*)bk + recordShift) = nxtpage;

    bpm->markDirty(indexk);

    return 0;
}

/*
 * Update a record
 */
RC RM_FileHandle :: UpdateRec      (const RM_Record &rec)
{
    char* pData;
    RID rid;
    int pageID, slotID;

    rec.GetData(pData);
    rec.GetRid(rid);
    rid.GetSlotNum(slotID);
    rid.GetPageNum(pageID);

    int index;
    BufType b = rmm->bpm->getPage(this->fileID, pageID, index);
    char* bm = (char*) b;
    memcpy(bm + recordShift + 4 + recordSize * slotID, pData, recordSize); // copy data from pData
    rmm->bpm->markDirty(index);

    return 0;
}

/*
 * Write dirty page(s) to disk
 * TODO: ?
 */
RC RM_FileHandle :: ForcePages     (PageNum pageNum) const
{
    return 0;
}



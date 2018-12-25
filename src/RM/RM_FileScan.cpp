//
// Created by 杨乐 on 2018/11/4.
//

#include "rm_internal.h"

/*
 * Constructor
 */
RM_FileScan :: RM_FileScan  ()
{

}

/*
 * Destructor
 */
RM_FileScan :: ~RM_FileScan ()
{

}

/*
 * Initialize file scan
 */
RC RM_FileScan :: OpenScan     (const RM_FileHandle &fileHandle,
                                AttrType      attrType,
                                int           attrLength,
                                int           attrOffset,
                                CompOp        compOp,
                                const void    *value)
{
    // get info from filehandle
    fileHandle.Get(fileID, recordSize, recordPerpage, recordShift, fm, bpm);
    handle = &fileHandle;

    // get totalpage
    int index;
    BufType b = bpm->getPage(fileID, 0, index);
    totalpage = b[2]; // page range : 0 ~ totalpage
    bpm->access(index);

    // save args
    this->attrType = attrType;
    this->attrLength = attrLength;
    this->attrOffset = attrOffset;
    this->compOp = compOp;
    this->value = value;

    // rid initialize : set pageID = 1, slotID = 0
    currid.Set(1, 0);

    if(D) cerr << "Open Scan." << endl;
    if(D) cerr << "     Total page = " << totalpage << endl;
    if(D) cerr << "     Recs per page = " << recordPerpage << endl;

    return 0;
}

/*
 * Get next matching record
 */
RC RM_FileScan :: GetNextRec   (RM_Record &rec)
{
    if(D) cerr << "Get Next Rec." << endl;

    int index;
    int pageID = currid.Page();
    int slotID = currid.Slot();

    RM_Record tmprec;
    char *data, *dataoff;

    BufType b = bpm->getPage(fileID, pageID, index);

    int found = 0;

    while(found == 0)
    {
        bpm->access(index);

        if(pageID > totalpage) return RM_EOF;

        if(slotID == recordPerpage)
        {
            pageID ++;

            if(pageID > totalpage) return RM_EOF;

            slotID = 0;
            currid.Set(pageID, slotID);

            bpm->access(index); // mark access

            b = bpm->getPage(fileID, pageID, index); // refresh new page
        }

        if(slotID > recordPerpage) return RM_BAD_FILESCAN;

        char* bitm = (char*) b + (slotID / 8);

        if(D) cerr << "    Get Rec, Page = " << currid.Page() << ", Slot = " << currid.Slot() << endl;

        if((*bitm) & (1 << (slotID % 8))) // record found
        {
            handle->GetRec(currid, tmprec);

            tmprec.GetData(data);
            dataoff = data + attrOffset;

            int flag = 0;

            if(compOp == NO_OP)
            {
                flag = 1;
            }
            else if(attrType == INT)
            {
                int src = *((int*) dataoff);
                int dst = *((int*) value);
                switch (compOp)
                {
                    case EQ_OP: flag = (src == dst); break;
                    case NE_OP: flag = (src != dst); break;
                    case LT_OP: flag = (src <  dst); break;
                    case GT_OP: flag = (src >  dst); break;
                    case LE_OP: flag = (src <= dst); break;
                    case GE_OP: flag = (src >= dst); break;
                    case NO_OP: flag = 1; break;
                    default: break;
                }
            }
            else if(attrType == FLOAT)
            {
                float src = *((float*) dataoff);
                float dst = *((float*) value);
                switch (compOp)
                {
                    case EQ_OP: flag = (src == dst); break;
                    case NE_OP: flag = (src != dst); break;
                    case LT_OP: flag = (src <  dst); break;
                    case GT_OP: flag = (src >  dst); break;
                    case LE_OP: flag = (src <= dst); break;
                    case GE_OP: flag = (src >= dst); break;
                    case NO_OP: flag = 1; break;
                    default: break;
                }
            }
            else if(attrType == STRING)
            {
                string src = dataoff;
                string dst = (char*) value;

                switch (compOp)
                {
                    case EQ_OP: flag = (src == dst); break;
                    case NE_OP: flag = (src != dst); break;
                    case LT_OP: flag = (src <  dst); break;
                    case GT_OP: flag = (src >  dst); break;
                    case LE_OP: flag = (src <= dst); break;
                    case GE_OP: flag = (src >= dst); break;
                    case NO_OP: flag = 1; break;
                    default: break;
                }
            }
            else
            {
                return RM_BAD_FILESCAN;
            }

            if(flag)
            {
                if(D) cerr << "Rec Get." << endl;
                handle->GetRec(currid, rec);
                found = 1;
            }

        }

        ++ slotID;
        currid.Set(pageID, slotID);
    }

    return 0;
}

/*
 * Terminate file scan
 */
RC RM_FileScan :: CloseScan    ()
{
    return 0;
}

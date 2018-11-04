//
// Created by 杨乐 on 2018/11/4.
//

#include "rm.h"
#include "../PF/bufmanager/BufPageManager.h"
#include "../PF/fileio/FileManager.h"


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
                                void          *value,
                                ClientHint    pinHint = NO_HINT)
{
    return 0;
}

/*
 * Get next matching record
 */
RC RM_FileScan :: GetNextRec   (RM_Record &rec)
{
    return 0;
}

/*
 * Terminate file scan
 */
RC RM_FileScan :: CloseScan    ()
{
    return 0;
}

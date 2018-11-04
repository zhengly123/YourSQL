//
// Created by 杨乐 on 2018/11/4.
//

#include "rm.h"
#include "../PF/bufmanager/BufPageManager.h"
#include "../PF/fileio/FileManager.h"

/*
 * Constructor
 */
RM_Manager :: RM_Manager  (FileManager* fm, BufPageManager* bpm)
{
    this->fm = fm;
    this->bpm = bpm;
}

/*
 * Destructor
 * TODO: ?
 */
RM_Manager :: ~RM_Manager ()
{

}

/*
 * Create a new file
 */
RC RM_Manager :: CreateFile  (const char *fileName, int recordSize)
{
    // Creating new file
    this->fm->createFile(fileName);

    // Open the file
    int fileID;
    this->fm->openFile(fileName, fileID);

    // RecordSize : Storing appropriate info in the header page
    int index;
    BufType b = this->bpm->allocPage(fileID, 0, index, false);
    b[0] = recordSize;
    this->bpm->markDirty(index);

    return 0;
}

/*
 * Destroy a file
 * TODO: ?
 */
RC RM_Manager :: DestroyFile (const char *fileName)
{
    return 0;
}

/*
 * Open a file
 *
 */
RC RM_Manager :: OpenFile    (const char *fileName, RM_FileHandle &fileHandle)
{
    int fileID;
    this->fm->openFile(fileName, fileID);
    fileHandle.SetID(fileID);
    fileHandle.SetRmm(this);

    int index, recordSize;
    BufType b = this->bpm->getPage(fileID, 0, index);
    recordSize = b[0]; // Get Recordsize from Page#0, Line0
    fileHandle.SetRecordSize(recordSize);
    this->bpm->access(index);
    return 0;
}

/*
 * Close a file
 */
RC RM_Manager :: CloseFile   (RM_FileHandle &fileHandle)
{
    int fileID;
    fileHandle->GetID(fileID);
    this->fm->closeFile(fileID);
}


//
// Created by 杨乐 on 2018/11/4.
//

#include "rm_internal.h"

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

int RM_Manager :: maxSlotnum(int recordSize)
{
    int l = 0, r = PAGE_SIZE;
    for(; l <= r; )
    {
        int m = (l + r) >> 1;
        int tbyte = recordSize * m + 4 + (m - 1) / 8 + 1;
        if(tbyte < PAGE_SIZE) l = m + 1; else r = m - 1;
    }
    return r;
}

/*
 * Create a new file
 */
RC RM_Manager :: CreateFile  (const char *fileName, int recordSize)
{
    if(D) cerr << "Create File : " << fileName << endl;

    // Creating new file
    this->fm->createFile(fileName);
    if(D) cerr << "    Creating Success." << endl;

    // Open the file
    int fileID, index;
    this->fm->openFile(fileName, fileID);
    if(D) cerr << "    Open Success, fileID = " << fileID << endl;

    // #0 : file header
    BufType b = this->bpm->allocPage(fileID, 0, index, false);

    b[0] = recordSize; // #0 : recordsize
    b[1] = maxSlotnum(recordSize); // #1 : records per pages
    b[2] = 1; // #2 : total page num
    b[3] = 1; // #3 : current empty page

    if(D) cerr << "    File Header (Page 0) Create Success" << endl;

    this->bpm->markDirty(index);

    // #1 : initial data page
    b = this->bpm->allocPage(fileID, 1, index, false);

    memset(b, 0, PAGE_SIZE); // refresh the page

    this->bpm->markDirty(index);
    this->bpm->close(fileID);

    if(D) cerr << "    File Page 1 Create Success" << endl;

    this->fm->closeFile(fileID);

    if(D) cerr << "    File Closed." << endl;

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
    if(D) cerr << "OpenFile : " <<  fileName << endl;
    int fileID;
    this->fm->openFile(fileName, fileID);

    if(D) cerr << "    Open success : file ID = " << fileID << endl;

    int index, recordSize, recordPerpage;
    BufType b = this->bpm->getPage(fileID, 0, index);
    recordSize = b[0]; // Get Recordsize from Page#0, Line#0
    recordPerpage = b[1]; // Get recordPerpage from Page#0, Line#1

    if(D) cerr << "   Record Size = " << recordSize <<
               "; Record Perpage = " << recordPerpage << endl;

    // Set the necessary message to fileHandle
    fileHandle.Set(fileID, this, this->fm, this->bpm, recordSize, recordPerpage);

    this->bpm->access(index);

    return 0;
}

/*
 * Close a file
 */
RC RM_Manager :: CloseFile   (RM_FileHandle &fileHandle)
{
    int fileID;
    fileHandle.GetID(fileID);
//    this->bpm->close();
//    this->fm->closeFile(fileID);
    this->bpm->close(fileID);
    this->fm->closeFile(fileID);
    return 0;
}


//
// Created by 杨乐 on 2018/11/4.
//

#ifndef YOURSQL_RM_H
#define YOURSQL_RM_H

#define PAGE_INT_NUM 2048

typedef int RC;
typedef unsigned int* BufType;
typedef int PageNum;
typedef int SlotNum;

class RM_Manager
{
public:
    FileManager* fm;
    BufPageManager* bpm;


    RM_Manager  (FileManager* fm, BufPageManager* bpm);            // Constructor
    ~RM_Manager ();                           // Destructor
    RC CreateFile  (const char *fileName, int recordSize); // Create a new file
    RC DestroyFile (const char *fileName);       // Destroy a file
    RC OpenFile    (const char *fileName, RM_FileHandle &fileHandle); // Open a file
    RC CloseFile   (RM_FileHandle &fileHandle);  // Close a file
};

class RM_FileHandle
{
    RM_Manager* rmm;
    int fileID;
    int recordSize;
public:
    RM_FileHandle  ();                                  // Constructor
    ~RM_FileHandle ();                                  // Destructor
    RC SetID          (int id);                         // Set file ID
    RC GetID          (int &id);                        // Get file ID
    RC SetRmm         (RM_Manager *rmm);                // Set RM_Manager
    RC SetRecordSize  (int RecordSize);                 // Set RecordSize
    RC GetRec         (const RID &rid, RM_Record &rec) const; // Get a record
    RC InsertRec      (const char *pData, RID &rid);       // Insert a new record, return record id
    RC DeleteRec      (const RID &rid);                    // Delete a record
    RC UpdateRec      (const RM_Record &rec);              // Update a record
    RC ForcePages     (PageNum pageNum = ALL_PAGES) const; // Write dirty page(s) to disk
};

class RM_FileScan {
public:
    RM_FileScan  ();                                // Constructor
    ~RM_FileScan ();                                // Destructor
    RC OpenScan     (const RM_FileHandle &fileHandle,  // Initialize file scan
                     AttrType      attrType,
                     int           attrLength,
                     int           attrOffset,
                     CompOp        compOp,
                     void          *value,
                     ClientHint    pinHint = NO_HINT);
    RC GetNextRec   (RM_Record &rec);                  // Get next matching record
    RC CloseScan    ();                                // Terminate file scan
};

class RM_Record
{
    char *pData;
    RID rid;
public:
    RM_Record  ();                     // Constructor
    ~RM_Record ();                     // Destructor
    RC GetData    (char *&pData) const;   // Set pData to point to the record's contents
    RC GetRid     (RID &rid) const;       // Get the record id

    RC SetData    (char *pData) const;   // Set pData to point to the record's contents
    RC SetRid     (RID rid) const;       // Set the record id
};

class RID
{
    PageNum pageNum;
    SlotNum slotNum;
public:
    RID        ();                        // Default constructor
    ~RID       ();                        // Destructor
    RID        (PageNum pageNum, SlotNum slotNum); // Construct RID from page and slot number
    RC Set        (PageNum pageNum, SlotNum slotNum); // Set RID from page and slot number
    RC GetPageNum (PageNum &pageNum) const;  // Return page number
    RC GetSlotNum (SlotNum &slotNum) const;  // Return slot number
};

#endif //YOURSQL_RM_H

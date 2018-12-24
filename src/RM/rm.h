//
// Created by 杨乐 on 2018/11/4.
//

#ifndef YOURSQL_RM_H
#define YOURSQL_RM_H

#include "../PF/bufmanager/BufPageManager.h"
#include "../PF/fileio/FileManager.h"
#include "../yoursql.h"
#include "RM_Error.h"

typedef int PageNum;
typedef int SlotNum;

class RID
{
    PageNum pageNum;
    SlotNum slotNum;
public:
    RID        ();                        // Default constructor
    ~RID       ();                        // Destructor
    RID        (PageNum pageNum, SlotNum slotNum); // Construct RID from page and slot number
    RC Set        (PageNum pageNum, SlotNum slotNum); // Set RID from page and slot number
    RC SetPageNum (PageNum pageNum); // Set RID from page and slot number
    RC SetSlotNum (SlotNum slotNum); // Set RID from page and slot number
    RC GetPageNum (PageNum &pageNum) const;  // Return page number
    RC GetSlotNum (SlotNum &slotNum) const;  // Return slot number
    PageNum GetPageNum () const;  // Return slot number
    SlotNum GetSlotNum () const;  // Return slot number
    bool operator ==(RID &b) const;
    PageNum Page() const {return pageNum;} // Return page number
    SlotNum Slot() const {return slotNum;}  // Return slot number
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

    RC SetData    (char *pData);   // Set pData to point to the record's contents
    RC SetRid     (RID rid);       // Set the record id
};

class RM_Manager;

class RM_FileHandle
{
    RM_Manager* rmm;
    FileManager* fm;
    BufPageManager* bpm;
    int fileID;
    int recordSize;
    int recordPerpage;
    int recordShift;
public:
    RM_FileHandle  ();                                  // Constructor
    ~RM_FileHandle ();                                  // Destructor
    RC Set            (int id,
                       RM_Manager* rmm,
                       FileManager* fm,
                       BufPageManager* bpm,
                       int recordSize,
                       int recordPerpage);              // Set Info
    RC Get             (int &fileID,
                       int &recordSize,
                       int &recordPerpage,
                       int &recordShift,
                       FileManager *&fm,
                       BufPageManager *&bpm) const;
    RC GetID          (int &id);                  // Get file ID
    RC GetRec         (const RID &rid, RM_Record &rec) const; // Get a record
    RC InsertRec      (const char *pData, RID &rid);       // Insert a new record, return record id
    RC DeleteRec      (const RID &rid);                    // Delete a record
    RC UpdateRec      (const RM_Record &rec);              // Update a record
    RC ForcePages     (PageNum pageNum) const; // Write dirty page(s) to dist
};

class RM_FileScan {
    FileManager* fm;
    BufPageManager* bpm;
    const RM_FileHandle* handle;
    int fileID;
    int recordSize;
    int recordPerpage;
    int recordShift;
    int totalpage;

    AttrType attrType;
    int attrLength;
    int attrOffset;
    CompOp compOp;
    const void* value;

    RID currid;
public:
    RM_FileScan  ();                                // Constructor
    ~RM_FileScan ();                                // Destructor
    RC OpenScan     (const RM_FileHandle &fileHandle,  // Initialize file scan
                     AttrType      attrType,
                     int           attrLength,
                     int           attrOffset,
                     CompOp        compOp,
                     const void    *value);
    RC GetNextRec   (RM_Record &rec);                  // Get next matching record
    RC CloseScan    ();                                // Terminate file scan
};

class RM_Manager
{
    int maxSlotnum(int recordsize);
    friend class RM_FileHandle;
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

#endif //YOURSQL_RM_H

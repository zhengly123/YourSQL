//
// Created by eric on 18-11-26.
//


#pragma once
#ifndef YOURSQL_IX_INDEXSCAN_H
#define YOURSQL_IX_INDEXSCAN_H

#include "../yoursql.h"
#include "IX_PRIVATE.h"

class IX_IndexScan {
public:
    IX_IndexScan  ();                                 // Constructor
    ~IX_IndexScan ();                                 // Destructor
    RC OpenScan      (const IX_IndexHandle &indexHandle, // Initialize index scan
                      CompOp      compOp,
                      void        *value,
                      ClientHint  pinHint = NO_HINT);
    RC GetNextEntry  (RID &rid);                         // Get next matching entry
    RC CloseScan     ();                                 // Terminate index scan
private:
    const IX_IndexHandle *indexHandle;
    RID iterator;
    CompOp compOp;
    char *targetValue[KEYSIZE];
};


#endif //YOURSQL_IX_INDEXSCAN_H

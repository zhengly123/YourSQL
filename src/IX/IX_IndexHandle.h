//
// Created by eric on 18-11-26.
//

#ifndef YOURSQL_IX_INDEXHANDLE_H
#define YOURSQL_IX_INDEXHANDLE_H

#include "../RM/rm.h"

class IX_IndexHandle {
public:
    IX_IndexHandle  ();                             // Constructor
    ~IX_IndexHandle ();                             // Destructor
    RC InsertEntry     (void *pData, const RID &rid);  // Insert new index entry
    RC DeleteEntry     (void *pData, const RID &rid);  // Delete index entry
    RC ForcePages      ();                             // Copy index to disk
};

#endif //YOURSQL_IX_INDEXHANDLE_H

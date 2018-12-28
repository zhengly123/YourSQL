//
// Created by 杨乐 on 2018/12/23.
//

#ifndef YOURSQL_QL_MANAGER_H
#define YOURSQL_QL_MANAGER_H

#include <vector>
#include <list>
#include "../IX/IX_PRIVATE.h"
#include "QL_PUBLIC.h"
#include "../SM/SM_PUBLIC.h"
#include "Selector.h"

class QL_Manager {
    SM_Manager *smm;
    IX_Manager *ixm;
    RM_Manager *rmm;
    RM_FileHandle handle;
    RM_FileScan rmscan;
public:
                                              // Constructor
      QL_Manager (SM_Manager &smm, IX_Manager &ixm, RM_Manager &rmm);
      ~QL_Manager ();                         // Destructor
    RC Select (int           nSelAttrs,        // # attrs in Select clause
              const RelAttr selAttrs[],       // attrs in Select clause
              std::list<std::string> rellist,
              int           nConditions,      // # conditions in Where clause
              const Condition conditions[]);  // conditions in Where clause
    RC Insert (const char  *relName,           // relation to insert into
              int         nValues,            // # values to insert
              const Value values[]);          // values to insert
    RC Delete (const char *relName,            // relation to delete from
              int        nConditions,         // # conditions in Where clause
              const Condition conditions[]);  // conditions in Where clause
    RC Update (const char *relName,            // relation to update
              int   nSet,
              const Condition sets[],
              int   nConditions,              // # conditions in Where clause
              const Condition conditions[]);  // conditions in Where clause

    RC showRelation   (const char *relName);

private:
    std::string relToFileName(const char *relName)
    {
        return std::string(relName)+std::string(".rel");
    }
};

#endif //YOURSQL_QL_MANAGER_H

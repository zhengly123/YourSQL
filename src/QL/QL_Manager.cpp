//
// Created by 杨乐 on 2018/12/23.
//

#include "QL_Manager.h"


QL_Manager :: QL_Manager (SM_Manager &smm, IX_Manager &ixm, RM_Manager &rmm)
{

}

QL_Manager :: ~QL_Manager ()                         // Destructor
{

}

RC QL_Manager :: Select (int           nSelAttrs,        // # attrs in Select clause
              const RelAttr selAttrs[],       // attrs in Select claus
              std::list<std::string> rellist,
              int           nConditions,      // # conditions in Where clause
              const Condition conditions[])  // conditions in Where clause
{

}


RC QL_Manager :: Insert (const char  *relName,           // relation to insert into
              int         nValues,            // # values to insert
              const Value values[])          // values to insert
{

}


RC QL_Manager :: Delete (const char *relName,            // relation to delete from
              int        nConditions,         // # conditions in Where clause
              const Condition conditions[])  // conditions in Where clause
{

}

RC QL_Manager :: Update (const char *relName,            // relation to update
              int 	nSet,
              const Condition sets[],
              int   nConditions,              // # conditions in Where clause
              const Condition conditions[])  // conditions in Where clause
{

}
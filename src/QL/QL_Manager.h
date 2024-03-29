//
// Created by 杨乐 on 2018/12/23.
//

#ifndef YOURSQL_QL_MANAGER_H
#define YOURSQL_QL_MANAGER_H

#include <vector>
#include <list>
#include "../IX/IX_PRIVATE.h"
#include "../SM/SM_PUBLIC.h"
#include "Selector.h"
#include "../Printer/StdoutPrinter.h"
#include "QL_PRIVATE.h"

class QL_Manager {
    SM_Manager *smm;
    IX_Manager *ixm;
    RM_Manager *rmm;
    RM_FileHandle handle;
    RM_FileScan rmscan;
public:
                                              // Constructor
      QL_Manager (SM_Manager &smm, IX_Manager &ixm, RM_Manager &rmm, Printer *printer);
      ~QL_Manager ();                         // Destructor
    RC Select (int           nSelAttrs,        // # attrs in Select clause
              RelAttr selAttrs[],       // attrs in Select clause
              std::list<std::string> rellist,
              int           nConditions,      // # conditions in Where clause
              Condition conditions[],  // conditions in Where clause
              int           nGroups,         // # attrs in Group By clause
              const RelAttr grpAttrs[],     // attrs in Group By clause
              int           nOrders,         // # attrs in Order By clause
              const RelAttr ordAttrs[]);     // attrs in Order By clause

    RC Insert (const char  *relName,           // relation to insert into
              int         nValues,            // # values to insert
              Value values[]);          // values to insert

    RC Delete (const char *relName,            // relation to delete from
              int        nConditions,         // # conditions in Where clause
              const Condition conditions[]);  // conditions in Where clause

    RC Update (const char *relName,            // relation to update
              int   nSet,
              const Condition sets[],
              int   nConditions,              // # conditions in Where clause
              const Condition conditions[]);  // conditions in Where clause

    RC showRelation   (const char *relName);
    /**
     * Print relation to printer
     * @param relName
     * @return
     */
    RC printRelation  (const char *relName);

    void setCheckPrimary(int flag) {checkPrimaryKey = flag;}
    Printer* getPrinter();
    void setPrinter(Printer*);

    int selectsize;
private:
    Printer *printer;
    int checkPrimaryKey;

    std::string relToFileName(const char *relName)
    {
        return std::string(relName)+std::string(".rel");
    }

    RC checkRelLegal(const std::vector<std::string> &relVec, const char *relName);
    RC checkAttrLegal(const vector<AttrInfo> &attributes, const char *attrName);
    RC checkAttrLegal(const vector<AttrInfo> &attributes, const RelAttr relAttr);
    RC getAttrIndex(const vector<AttrInfo> &attributes, const RelAttr relAttr);

    RC getRelIndex(const std::vector<std::string> &relVec, const char *relName);

    /**
     * Create or retrieve IndexHandle from selector.
     * @param indexHandle
     * @param relName
     * @param attr
     * @param selector
     * @return
     */
    RC getIndexHandle(IX_IndexHandle **indexHandle, const char *relName,
                      const AttrInfo attr, Selector &selector);

    /**
     * If indexHandle is created by getIndexHandle, close and release it.
     * @param indexHandle
     * @param attr
     * @param selector
     * @return
     */
    RC disposeHandle(IX_IndexHandle *indexHandle, const AttrInfo attr,
                     Selector &selector);
};

#endif //YOURSQL_QL_MANAGER_H

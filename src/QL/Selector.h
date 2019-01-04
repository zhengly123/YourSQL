//
// Created by eric on 18-12-28.
//

#ifndef YOURSQL_SELECTOR_H
#define YOURSQL_SELECTOR_H

#include <vector>
#include <list>
//#include "../IX/IX_PRIVATE.h"
#include "../IX/IX_PRIVATE.h"
//#include "../QL/QL_PUBLIC.h"
#include "../SM/SM_PUBLIC.h"

class Selector
{
public:
//    SM_Manager *smm;
    IX_Manager *ixm;
    RM_Manager *rmm;
    RelationMeta relmeta;
    vector<AttrInfo> attrs;
    vector<Condition> conditions;
    RM_FileHandle handle;
    RM_FileScan scan;
    bool dead;
    int errorReason;
    int errorIndex;

    Selector(IX_Manager *ixm,
             RM_Manager *rmm,
             const char *relName,
             RelationMeta relmeta,
             vector<AttrInfo> attributes,
             int nConditions,              // # conditions in Where clause
             const Condition conditions[],  // conditions in Where clause
             RM_FileHandle SMhandle,
             bool interTable = false
             );
    ~Selector();
    void iterateOptimize();
    /**
     * Check whether condition is legal.
     * @return return false if there are illegal sets, and set error indicator.
     */
    bool checkConditionLegal();
    /**
     * Check legality for sets
     * @param nSet
     * @param sets
     * @return return false if there are illegal sets, and set error indicator.
     */
    bool checkSetLegal(int nSet, const Condition sets[]);
    int getNext(RM_Record &outRecord, RM_FileHandle *&outHandle);
    /**
     * Get AttrInfo against attr name. It should be assumed the attr exist in
     * the selector. Otherwise, an assert is triggered.
     * @param attr
     * @return
     */
    AttrInfo getAttr(char *attr);
//    void remove();

private:
    auto checkAttrExist(char *attrName);
    /**
     * Check whether a tuple fits a condition
     * @param cond
     * @param data
     * @return
     */
    bool checkCondition(Condition cond, void *data);
};


#endif //YOURSQL_SELECTOR_H

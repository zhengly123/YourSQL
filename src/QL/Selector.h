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
             int   nConditions,              // # conditions in Where clause
             const Condition conditions[]);  // conditions in Where clause
    ~Selector();
    void iterateOptimize();
    bool checkConditionLegal();
    int getNext(RM_Record &outRecord, RM_FileHandle *&outHandle);
//    void remove();

private:
//    vector<AttrInfo> lhsAttrs;
//    vector<AttrInfo> rhsAttrs;
    auto checkAttrExist(char *attrName);
    bool checkCondition(Condition cond, void *data);
};


#endif //YOURSQL_SELECTOR_H

//
// Created by 杨乐 on 2018/12/23.
//

#include <cstring>
#include "QL_Manager.h"


QL_Manager::QL_Manager(SM_Manager &smm, IX_Manager &ixm, RM_Manager &rmm, Printer *printer)
        : printer(printer)
{
    this->rmm = &rmm;
    this->ixm = &ixm;
    this->smm = &smm;
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

/**
 * Insert a tuple to a relation.
 * @param relName, nValues, values
 * @return 0 if normal, positive if warning
 **/
RC QL_Manager :: Insert (const char  *relName,           // relation to insert into
              int         nValues,            // # values to insert
              const Value values[])          // values to insert
{
    struct RelationMeta relmeta;

    if(smm->relGet(relName, &relmeta)) return QL_RELNOTEXIST;
    if(relmeta.attrCount != nValues) return QL_INVALIDSIZE;

    vector<AttrInfo> attributes;
    AttrInfo curAttr;
    attributes = smm->attrGet(relName);

    for(int i = 0; i < nValues; ++ i)
    {
        curAttr = attributes[i];

        // Null type can be applied to every type
        if(values[i].type == NULLTYPE)
        {
            if(curAttr.flag & 1) return QL_ATTRNOTNULL;
        }
        else if(curAttr.attrType != values[i].type) return QL_TYPEUNMATCHED;

        //TODO: MAXNAME是最大的表名字、属性名字？
        if(values[i].type == STRING && strlen((char*)values[i].data) > MAXNAME) return QL_STRTOOLONG;
    }

    // TODO: Check primary key!

    int tuplelength = relmeta.tupleLength;
    int ifnull = relmeta.tupleLength - relmeta.attrCount;

    char *buffer = new char[tuplelength];

    for(int i = 0; i < nValues; ++ i)
    {
        if(values[i].type != NULLTYPE)
            memcpy(buffer + attributes[i].offset, values[i].data, attributes[i].attrLength),
            *(buffer + ifnull + i) = 0; // null flag set
        else
            *(buffer + ifnull + i) = 1; // null flag set
    }

    rmm->OpenFile(relToFileName(relName).data(), handle);

    RID rid;
    handle.InsertRec(buffer, rid);

    // TODO: insert it into index!

    rmm->CloseFile(handle);

    return 0;
}


RC QL_Manager :: Delete (const char *relName,            // relation to delete from
              int        nConditions,         // # conditions in Where clause
              const Condition conditions[])  // conditions in Where clause
{
    RelationMeta relmeta;
    if(smm->relGet(relName, &relmeta)) return QL_RELNOTEXIST;
    vector<AttrInfo> attributes;
    attributes = smm->attrGet(relName);
//    for (int i = 0; i < nConditions; ++i)
//    {
//        if (!checkConditionLegal(relmeta, conditions[i])) return QL_CONDITION_INVALID;
//    }
    Selector selector(ixm,rmm, relName, relmeta, attributes,
            nConditions, conditions);
    RM_Record record;
    RM_FileHandle *handle = nullptr;
    RID rid;
    int cnt=0;
    while (selector.getNext(record, handle))
    {
        record.GetRid(rid);
        handle->DeleteRec(rid);
        cnt++;
    }
    printf("INFO: delete cnt=%d\n", cnt);
    return 0;
}

RC QL_Manager :: Update (const char *relName,            // relation to update
              int 	nSet,
              const Condition sets[],
              int   nConditions,              // # conditions in Where clause
              const Condition conditions[])  // conditions in Where clause
{
    RelationMeta relmeta;
    if(smm->relGet(relName, &relmeta)) return QL_RELNOTEXIST;
    vector<AttrInfo> attributes;
    attributes = smm->attrGet(relName);
    Selector selector(ixm,rmm, relName, relmeta, attributes,
                      nConditions, conditions);
    // check legality of SETs
    selector.checkSetLegal(nSet, sets);
    RM_Record record;
    RM_FileHandle *handle = nullptr;
    RID rid;
    int cnt=0;
    while (selector.getNext(record, handle))
    {
        record.GetRid(rid);
        char *data;
        record.GetData(data);
        for (int i = 0; i < nSet; ++i)
        {
            const Condition &set=sets[i];
            AttrInfo attr=selector.getAttr(set.lhsAttr.attrName);
            if (set.rhsValue.type == AttrType::NULLTYPE)
            {
                *(data + attr.nullOffset) = 1;
            } else
            {
                *(data + attr.nullOffset) = 0;
                memcpy(data + attr.offset, set.rhsValue.data, attr.attrLength);
            }
        }
        handle->UpdateRec(record);
        cnt++;
    }
    printf("INFO: Update cnt=%d\n", cnt);
    return 0;
}

RC QL_Manager :: printRelation   (const char *relName)
{
    struct RelationMeta relmeta;

    if(smm->relGet(relName, &relmeta)) return QL_RELNOTEXIST;

    vector<AttrInfo> attributes;
    AttrInfo curAttr;

    attributes = smm->attrGet(relName);
    rmm->OpenFile(relToFileName(relName).data(), handle);

    rmscan.OpenScan(handle, INT, 0, 0, NO_OP, NULL);

    RM_Record rec;
    char* buffer;
    char* ifnullbuf;

    for(int i = 0; i < attributes.size(); ++ i)
    {
        if(attributes[i].attrType == INT)
            printer->getSS()<<"       INT      ";
        else if(attributes[i].attrType == STRING)
            printer->getSS()<<"     STRING     ";
        else
            printer->getSS()<<"       ***      ";
    }
    printer->getSS()<<"\n";

    int tuplelength = relmeta.tupleLength;
    int ifnull = relmeta.tupleLength - relmeta.attrCount;

    while(rmscan.GetNextRec(rec) != RM_EOF)
    {
        rec.GetData(buffer);
        ifnullbuf = buffer + ifnull;

        for(int i = 0; i < attributes.size(); ++ i)
        {
            char* data = buffer + attributes[i].offset;
            if(*(ifnullbuf + i) == 1)
                printer->getSS() << "      NULL      ";
            else if(attributes[i].attrType == INT)
                printer->getSS() << *(int *) data<<" ";
            else if(attributes[i].attrType == STRING)
                printer->getSS() << data <<" ";
            else
                printer->getSS() << "       ***      ";
        }
        printer->getSS() << " \n";
    }

    rmscan.CloseScan();
    rmm->CloseFile(handle);
    return 0;
}

RC QL_Manager :: showRelation   (const char *relName)
{
    // for gtest
#ifdef GTEST
    return printRelation(relName);
#endif

    struct RelationMeta relmeta;

    if(smm->relGet(relName, &relmeta)) return QL_RELNOTEXIST;

    vector<AttrInfo> attributes;
    AttrInfo curAttr;

    attributes = smm->attrGet(relName);
    rmm->OpenFile(relToFileName(relName).data(), handle);

    rmscan.OpenScan(handle, INT, 0, 0, NO_OP, NULL);

    RM_Record rec;
    char* buffer;
    char* ifnullbuf;

    printf("+");
    for(int i = 0; i < attributes.size(); ++ i)
        if(i == 0)
            printf("---------------");
        else
            printf("----------------");
    printf("+\n");

    for(int i = 0; i < attributes.size(); ++ i)
    {
        if(attributes[i].attrType == INT)
            printf("|      INT      ");
        else if(attributes[i].attrType == STRING)
            printf("|    STRING     ");
        else
            printf("|      ***      ");
    }
    printf("|\n");

    printf("+");
    for(int i = 0; i < attributes.size(); ++ i)
        if(i == 0)
            printf("---------------");
        else
            printf("----------------");
    printf("+\n");

    int tuplelength = relmeta.tupleLength;
    int ifnull = relmeta.tupleLength - relmeta.attrCount;

    while(rmscan.GetNextRec(rec) != RM_EOF)
    {
        rec.GetData(buffer);
        ifnullbuf = buffer + ifnull;

        for(int i = 0; i < attributes.size(); ++ i)
        {
            char* data = buffer + attributes[i].offset;
            if(*(ifnullbuf + i) == 1)
                printf("|     NULL      ");
            else if(attributes[i].attrType == INT)
                printf("|% 9d      ", *(int*)data);
            else if(attributes[i].attrType == STRING)
                printf("|% 9s      ", data);
            else
                printf("|      ***      ");
        }
        printf("|\n");

        printf("+");
        for(int i = 0; i < attributes.size(); ++ i)
            if(i == 0)
                printf("---------------");
            else
                printf("----------------");
        printf("+\n");
    }

    rmscan.CloseScan();
    rmm->CloseFile(handle);
    return 0;
}

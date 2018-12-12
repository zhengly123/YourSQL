//
// Created by 杨乐 on 2018/12/10.
//

#include <cstring>
#include <string>
#include <set>
#include "SM_Manager.h"
const char* RELCAT="relcat";
const char* ATTRCAT="attrcat";

SM_Manager::SM_Manager(IX_Manager &ixm, RM_Manager &rmm)
        : ixm(&ixm), rmm(&rmm)
{

}

SM_Manager :: ~SM_Manager ()
{

}

// Open database
RC SM_Manager :: OpenDb      (const char *dbName)
{
    RC rc;
    cerr << "Opening DB : " << dbName << endl;
    if (strcmp(dbName, RELCAT) == 0 || strcmp(dbName, ATTRCAT) == 0)
    {
        return SM_INVALID_DB_NAME;
    }

    assert(getcwd(initialCwd, 2048));
    assert(chdir(dbName));

    assert((rc=rmm->OpenFile(RELCAT,relcatHandler))==0);
    assert((rc=rmm->OpenFile(ATTRCAT,attrcatHandler))==0);

    isOpen=true;
    return 0;
}

// Close database
RC SM_Manager :: CloseDb     ()
{
    rmm->CloseFile(relcatHandler);
    rmm->CloseFile(attrcatHandler);
    isOpen = false;
    assert(chdir(initialCwd)==0);

    return 0;
}

// Create relation
RC SM_Manager :: CreateTable (const char *relName, int attrCount, AttrInfo *attributes)
{
    RC rc;
    if (strlen(relName)>MAXNAME)
        return SM_NAME_TOO_LONG;
    int relSize=0;
    std::set<std::string> nameSet;
    RelationMeta relationMeta={};
    for (int i=0;i<attrCount;++i)
    {
        if (nameSet.find(string(attributes[i].attrName))!=nameSet.end())
            return SM_SAME_NAME_ATTR;
        nameSet.insert(string(attributes[i].attrName));
        attributes[i].offset = relSize;
        memset(&attributes[i].relName, 0, MAXNAME+1);//make sure the vacant part is zero
        strcpy(attributes[i].relName, relName);
        relSize += attributes[i].attrLength;
    }
    relationMeta.attrCount=attrCount;
    relationMeta.indexCount=0;
    strcpy(relationMeta.relName,relName);
    relationMeta.tupleLength=relSize;
    // check empty part of relation name
    for (int i = strlen(relName); i < MAXNAME + 1; ++i)
        assert(relationMeta.relName[i] == 0);

    RID rid;
    rc = relcatHandler.InsertRec(reinterpret_cast<char *>(&relationMeta), rid);
    assert(rc==0);
    for (int i = 0; i < attrCount; ++i)
    {
        assert((rc = attrcatHandler.InsertRec((char *) (attributes + i), rid)) == 0);
    }
    rc = rmm->CreateFile(relName, relationMeta.tupleLength);
    assert(rc==0);
    return 0;
}

// Destroy relation
RC SM_Manager :: DropTable   (const char *relName)
{

}

// Create index
RC SM_Manager :: CreateIndex (const char *relName, const char *attrName)
{
    RM_FileScan attrScan,relationScan;
    RM_Record relRecord, attrRecord;
    RC rc;
    char *pData;
    bool hit = false;
    RelationMeta *relationMeta=nullptr;
    relationScan.OpenScan(relcatHandler, AttrType::STRING, strlen(relName) + 1, 0,
                          CompOp::EQ_OP, (void *)relName);
    attrScan.OpenScan(attrcatHandler, AttrType::STRING, strlen(relName) + 1, 0,
                      CompOp::EQ_OP, (void *)(relName));
    while (relationScan.GetNextRec(relRecord) != RM_EOF)
    {
        char *tempData;
        relRecord.GetData(tempData);
        relationMeta = (RelationMeta *) tempData;
        hit=true;
        break;
    }
    relationScan.CloseScan();
    // if not find the relation
    if (!hit)
        return SM_NONEXIST_RELATION;

    // search the attribution
    AttrInfo* attrInfo;
    int indexNum;
    hit=false;
    while (attrScan.GetNextRec(attrRecord) != RM_EOF)
    {
        relRecord.GetData(pData);

        if (strcmp(((AttrInfo *) pData)->attrName, attrName) == 0)
        {
            char *tempData;
            attrRecord.GetData(tempData);
            attrInfo=(AttrInfo*)tempData;
            rc = ixm->CreateIndex(relName, indexNum = relationMeta->indexCount++,
                                  attrInfo->attrType, attrInfo->attrLength);
            if (rc)
            {
                cerr << "Create index error: " << rc << endl;
            }
            assert(rc==0);
            relcatHandler.UpdateRec(relRecord);
            hit = true;
            break;
        }
    }
    attrScan.CloseScan();
    if (!hit)
        return SM_NONEXIST_RELATION;

    // Open table and read data to build the index
    RM_FileHandle tableHandle;
    RM_FileScan fileScan;
    RM_Record entryRecord;
    IX_IndexHandle ixIndexHandle;
    ixm->OpenIndex(relName, indexNum, ixIndexHandle);
    rmm->OpenFile(relToFileName(relName).data(),tableHandle);
    fileScan.OpenScan(tableHandle, attrInfo->attrType, attrInfo->attrLength,
                      attrInfo->offset, NO_OP, nullptr);
    // iterate entry and insert into indexHandler
    while (attrScan.GetNextRec(entryRecord))
    {
        char *tempData;
        RID rid;
        entryRecord.GetData(tempData);
        entryRecord.GetRid(rid);
        ixIndexHandle.InsertEntry(tempData + attrInfo->offset, rid);
    }
    ixIndexHandle.ForcePages();
    fileScan.CloseScan();
}

// Destroy index
RC SM_Manager :: DropIndex   (const char *relName, const char *attrName)
{

}

// Load utility
RC SM_Manager :: Load        (const char *relName, const char *fileName)
{

}

// Help for database
RC SM_Manager :: Help        ()
{

}

// Help for relation
RC SM_Manager :: Help        (const char *relName)
{

}

// Print relation
RC SM_Manager :: Print       (const char *relName)
{

}

// Set system parameter
RC SM_Manager :: Set         (const char *paramName, const char *value)
{

}

RC SM_Manager::createDb(const char *dbName)
{
    if (mkdir(dbName,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
        return SM_SYSCALL_ERROR;
    RC rc;
    rc = rmm->CreateFile(RELCAT, sizeof(RelationMeta));
    assert(rc==0);
    rc = rmm->CreateFile(ATTRCAT, sizeof(AttrInfo));
    assert(rc==0);
    return 0;
}


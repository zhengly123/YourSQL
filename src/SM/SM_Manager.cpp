//
// Created by 杨乐 on 2018/12/10.
//

#include <cstring>
#include <string>
#include <set>
#include <cstddef>
#include <sys/stat.h>//to check if a folder exists
#include "SM_Manager.h"
#include "../Printer/StdoutPrinter.h"
const char* RELCAT="relcat";
const char* ATTRCAT="attrcat";

SM_Manager::SM_Manager(IX_Manager &ixm, RM_Manager &rmm)
        : ixm(&ixm), rmm(&rmm), isOpen(false), currentDbName()
{
    printer = new StdoutPrinter();
}

SM_Manager::SM_Manager(IX_Manager &ixm, RM_Manager &rmm, Printer *printer)
:ixm(&ixm), rmm(&rmm), isOpen(false), currentDbName(), printer(printer)
{

}

SM_Manager :: ~SM_Manager ()
{
    printer->flush();
    if (isOpen)
        CloseDb();
}

// Open database
RC SM_Manager :: OpenDb      (const char *dbName)
{
    RC rc;
    // cerr << "Opening DB : " << dbName << endl;
    if (strcmp(dbName, RELCAT) == 0 || strcmp(dbName, ATTRCAT) == 0)
    {
        return SM_INVALID_DB_NAME;
    }
    auto pTemp = getcwd(initialCwd, 2048);
    assert(pTemp);
    const basic_string<char, char_traits<char>, allocator<char>> &absolutePath =
            string(initialCwd) + string("/") + string(dbName);
    rc = chdir(absolutePath.data());
//    printf("err:%d\n", errno);
    assert(rc==0);

    rc=rmm->OpenFile(RELCAT,relcatHandler);
    assert(rc==0);
    rc=rmm->OpenFile(ATTRCAT,attrcatHandler);
    assert(rc==0);

    isOpen=true;
    currentDbName=std::string(dbName);
    smFileHandle.clear();
    return 0;
}

// Close database
RC SM_Manager :: CloseDb     ()
{
    if (isOpen)
    {
        rmm->CloseFile(relcatHandler);
        rmm->CloseFile(attrcatHandler);
        isOpen = false;
        assert(chdir(initialCwd)==0);

        for(auto it : smFileHandle) rmm->CloseFile(it.second);
        smFileHandle.clear();

        for(auto it : ixIndexHandle)
        {
            ixm->CloseIndex(*it.second);
            delete it.second;
        }
        ixIndexHandle.clear();
    } else{
        printer->getSS() << "No database is opened.\n";
    }
    return 0;
}

// Create relation
RC SM_Manager :: CreateTable (const char *relName, int attrCount, AttrInfo *attributes)
{
    RC rc;
    if (strlen(relName)>MAXNAME)
        return SM_NAME_TOO_LONG;

    if (relExist(std::string(relName)))
    {
        // printer->getSS()<<"Same name relation exists\n";
        return SM_TABLE_EXIST;
    }

    // Resolve Foreign Key First : Assert their attrType & attrLength

    for(int i=0;i<attrCount;++i)
        if(attributes[i].isForeign)
        {
            RelAttr relattr;
            AttrInfo atr;
            std::string relName(attributes[i].foreignTable);
            std::string attrName(attributes[i].foreignName);
            if(attrGet(std::make_pair(relName, attrName), &atr)) return SM_FOREIGN_NOTFOUND;
            if(!(atr.flag & 2)) return SM_FOREIGN_NOTPRIMARY;
            if(attributes[i].attrType != atr.attrType) return SM_FOREIGN_TYPEMISMATCH;
            if(attributes[i].attrLength != atr.attrLength) return SM_FOREIGN_TYPEMISMATCH;
            atr.refcnt ++;
            if(attrRefresh(relName, attrName, &atr)) return SM_FOREIGN_NOTFOUND;
        }


    int relSize=0;
    std::set<std::string> nameSet;
    RelationMeta relationMeta={};
    for (int i=0;i<attrCount;++i)
    {
        if (nameSet.find(string(attributes[i].attrName))!=nameSet.end())
            return SM_SAME_NAME_ATTR;
        nameSet.insert(string(attributes[i].attrName));
        attributes[i].offset = relSize;
        attributes[i].indexNum = 0;
        memset(&attributes[i].relName, 0, MAXNAME+1); // make sure the vacant part is zero
        strcpy(attributes[i].relName, relName);
        relSize += attributes[i].attrLength;
    }
    // calculate null flag offset
    for (int i = 0; i < attrCount; ++i)
    {
        attributes[i].nullOffset = relSize + i;
    }
    relationMeta.attrCount=attrCount;
    relationMeta.indexCount=0;
    strcpy(relationMeta.relName,relName);
    // attrCount : IF NULL FLAG
    // TODO: in fact, it should be ceil(attrcount / 8)
    relationMeta.tupleLength=relSize+attrCount;
    // check empty part of relation name
    for (int i = strlen(relName); i < MAXNAME + 1; ++i)
        relationMeta.relName[i] = 0;

    RID rid;
    rc = relcatHandler.InsertRec(reinterpret_cast<char *>(&relationMeta), rid);
//    relcatHandler.ForcePages(rid.Page());
    assert(rc==0);
    for (int i = 0; i < attrCount; ++i)
    {
        rc = attrcatHandler.InsertRec((char *) (attributes + i), rid);
        assert(rc == 0);
    }
    rc = rmm->CreateFile(relToFileName(relName).data(), relationMeta.tupleLength);
    assert(rc==0);
//    rmm->CloseFile(relcatHandler);
//    rmm->CloseFile(attrcatHandler);

    return 0;
}

/**
 * Destroy relation
 * @param relName
 * @return
 * @todo 没有删除对应的index
 */
RC SM_Manager :: DropTable   (const char *relName)
{
    RC rc;
    if (strlen(relName)>MAXNAME)
        return SM_NAME_TOO_LONG;

    vector<AttrInfo> attributes =  attrGet(relName);
    for(auto attr : attributes)
        if(attr.refcnt) return SM_FOREIGN_REF_DROP_ERROR;

    for(auto attr : attributes)
        if(attr.isForeign)
        {
            AttrInfo refatr;
            std::string relName(attr.foreignTable);
            std::string attrName(attr.foreignName);
            if(attrGet(std::make_pair(relName, attrName), &refatr)) return SM_FOREIGN_NOTFOUND;
            refatr.refcnt --;
            if(attrRefresh(relName, attrName, &refatr)) return SM_FOREIGN_NOTFOUND;
        }


    RM_FileScan relScan;
    RM_Record relRecord;
    RID rid;
    char *pData;

    bool hit=false;
    relScan.OpenScan(relcatHandler,AttrType::STRING,MAXNAME+1,
            offsetof(RelationMeta,relName), CompOp::EQ_OP, (void *)relName);

    while (relScan.GetNextRec(relRecord)!=RM_EOF)
    {
        hit=true;

        relRecord.GetRid(rid);
        rc=relcatHandler.DeleteRec(rid);
        assert(rc==0);
        rc=rmm->DestroyFile(relToFileName(relName).data());
        smFileHandle.erase(std::string(relName)); // erase from the sm handle
        assert(rc==0);
        break;
    }
    relScan.CloseScan();

    RM_FileScan attrScan;
    attrScan.OpenScan(attrcatHandler,AttrType::STRING,MAXNAME+1,
                      offsetof(AttrInfo,relName), CompOp::EQ_OP, (void *)relName);
    while (attrScan.GetNextRec(relRecord) != RM_EOF)
    {
        relRecord.GetRid(rid);
        if(rc = attrcatHandler.DeleteRec(rid)) return rc;
    }
    attrScan.CloseScan();

    if (!hit)
        return SM_NONEXIST_RELATION;
    return 0;
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
    attrScan.OpenScan(attrcatHandler, AttrType::STRING, strlen(attrName) + 1, 0,
                      CompOp::EQ_OP, (void *)(attrName));
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
        attrRecord.GetData(pData);

        // scan中保证了attrName一致，以下判断relName一致
        if (strcmp(((AttrInfo *) pData)->relName, relName) == 0)
        {
            // set record index
//            char *tempData;
//            attrRecord.GetData(tempData);
            attrInfo=(AttrInfo*)pData;
            rc = ixm->CreateIndex(relName, indexNum = ++relationMeta->indexCount,
                                  attrInfo->attrType, attrInfo->attrLength);
            attrInfo->indexNum=indexNum;
            attrcatHandler.UpdateRec(attrRecord);
            relcatHandler.UpdateRec(relRecord);

            if (rc)
            {
                cerr << "Create index error: " << rc << endl;
            }
            assert(rc==0);
//            relcatHandler.UpdateRec(relRecord);
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
    IX_IndexHandle *ixIndexHandle;

    ixIndexHandle = indexhandleGet(std::string(relName), indexNum);
    tableHandle = filehandleGet(std::string(relName));

    //ixm->OpenIndex(relName, indexNum, ixIndexHandle);
    //rmm->OpenFile(relToFileName(relName).data(),tableHandle);

    fileScan.OpenScan(tableHandle, attrInfo->attrType, attrInfo->attrLength,
                      attrInfo->offset, NO_OP, nullptr);
    // iterate entry and insert into indexHandler
    while (fileScan.GetNextRec(entryRecord) != RM_EOF)
    {
        char *tempData;
        RID rid;
        entryRecord.GetData(tempData);
        entryRecord.GetRid(rid);
        ixIndexHandle->InsertEntry(tempData + attrInfo->offset, rid);
#ifdef OutputLinearIndex
        //debug
        fprintf(stderr, "After insert\n");
        ixIndexHandle->printBPT();
        ixIndexHandle->printLinearLeaves();
#endif
    }
#ifdef OutputLinearIndex
    //debug
    ixIndexHandle->printLinearLeaves();
#endif

    ixIndexHandle->ForcePages();
    //ixm->CloseIndex(ixIndexHandle);
    fileScan.CloseScan();
    //rmm->CloseFile(tableHandle);
    return 0;
}

// Destroy index
RC SM_Manager :: DropIndex   (const char *relName, const char *attrName)
{
    RM_FileScan attrScan, relScan;
    RM_Record attrRecord, relRecord;
    RC rc;
    bool hit = false;

//    relationScan.OpenScan(attrcatHandler, )
    attrScan.OpenScan(attrcatHandler, AttrType::STRING, strlen(relName) + 1,
                      offsetof(AttrInfo, relName),
                      CompOp::EQ_OP, (void *) (relName));

    // search the attribution and modify indexNum
    AttrInfo* attrInfo;
    char *pData;
    int indexNum;
    hit = false;
    while (attrScan.GetNextRec(attrRecord) != RM_EOF)
    {
        attrRecord.GetData(pData);

        // scan中保证了relName一致，以下判断attrName一致
        if (strcmp(((AttrInfo *) pData)->attrName, attrName) == 0)
        {
            // set record index
//            char *tempData;
//            attrRecord.GetData(tempData);
            attrInfo=(AttrInfo*)pData;
//            rc = ixm->CreateIndex(relName, indexNum = relationMeta->indexCount++,
//                                  attrInfo->attrType, attrInfo->attrLength);
            indexNum = attrInfo->indexNum;
            rc = ixm->DestroyIndex(relName, indexNum);
            ixIndexHandle.erase(getFileNameWithIndex(std::string(relName), indexNum));

            if (rc)
            {
                cerr << "Destory index error: " << rc << endl;
            }
            assert(rc==0);

            attrInfo->indexNum=0;
            attrcatHandler.UpdateRec(attrRecord);

            // No indexNum pool is maintained, so there is no reduction
            // update rel

            // No indexNum pool is maintained, so there is no reduction

            hit = true;
            break;
        }
    }
    attrScan.CloseScan();
    if (!hit)
        return SM_NONEXIST_RELATION;

//    relScan.OpenScan(relcatHandler,AttrType::STRING,strlen(relName)+1,
//                    offsetof(RelationMeta,relName), EQ_OP, relName);
//
//    relScan.GetNextRec(relRecord);
//
//    char *relData;
//    relRecord.GetData(relData);
//    ((RelationMeta*)relData)->indexCount--;
//    relcatHandler.UpdateRec(relRecord);
//
    return 0;
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

RC SM_Manager::CreateDb(const char *dbName)
{
    if (isOpen)
    {
        fprintf(stderr, "Close the database before creation\n");
        return SM_DB_NOT_CLOSE;
    }
    if (mkdir(dbName,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
        return SM_SYSCALL_ERROR;
    RC rc;
//    assert(getcwd(initialCwd, 2048));
//    const basic_string<char, char_traits<char>, allocator<char>> &absolutePath =
//            string(initialCwd) + string("/") + string(dbName);
//    rc = chdir(absolutePath.data());
//
    rc = rmm->CreateFile((string(dbName) + string("/") + string(RELCAT)).data(),
                         sizeof(RelationMeta));
    assert(rc==0);
    rc = rmm->CreateFile((string(dbName) + string("/") + string(ATTRCAT)).data(),
            sizeof(AttrInfo));
    assert(rc==0);

    return 0;
}

/**
 *
 * @param dbName
 * @return
 * @todo find a approciate way to delete dirctory
 */
RC SM_Manager::DestroyDb(const char *dbName)
{
    if (isOpen)
    {
        fprintf(stderr,"Close the database before destroy\n");
        return SM_DB_NOT_CLOSE;
    }
    if (strchr(dbName,'/')!=nullptr)
    {
        fprintf(stderr,"Illegal db name\n");
        return SM_ILLEGAL_NAME;
    }
    if (strchr(dbName, '.')!=nullptr)
    {
        fprintf(stderr,"Illegal db name\n");
        return SM_ILLEGAL_NAME;
    }
    struct stat sb;
    if (!(stat(dbName, &sb) == 0 && S_ISDIR(sb.st_mode)))
    {
        fprintf(stderr,"Database does not exist\n");
        return SM_DB_NOT_CLOSE;
    }
    system((std::string("rm -r ") + std::string(dbName)).data());
    return 0;
}

RC SM_Manager::PrintTables()
{
    cerr << "Show Tables: " << endl;
    RM_FileScan relScan;
    RM_Record relRecord;
    RC rc;
    bool hit=false;
    relScan.OpenScan(relcatHandler,AttrType::STRING,MAXNAME+1,
                     offsetof(RelationMeta,relName), CompOp::NO_OP, nullptr);
    //printer->Print("Show Tables :\n");
    while (relScan.GetNextRec(relRecord) != RM_EOF)
    {
        char *relationMetaData;
        relRecord.GetData(relationMetaData);
        printer->PrintTablesInfo((RelationMeta *) relationMetaData, 1);
    }
    printer->flush();
    return 0;
}

vector<RelationMeta> SM_Manager::TestReturnTables()
{
    RM_FileScan relScan;
    RM_Record relRecord;
    RC rc;
    vector<RelationMeta> ret;
    bool hit=false;
    relScan.OpenScan(relcatHandler,AttrType::STRING,MAXNAME+1,
                     offsetof(RelationMeta,relName), CompOp::NO_OP, nullptr);
    while (relScan.GetNextRec(relRecord) != RM_EOF)
    {
        char *relationMetaData;
        relRecord.GetData(relationMetaData);
//        printer->PrintTablesInfo((RelationMeta *) relationMetaData, 1);
        ret.push_back(*(RelationMeta *) relationMetaData);
    }
    return ret;
}

vector<AttrInfo> SM_Manager::TestReturnAttrs()
{
    RM_FileScan attrScan;
    RM_Record attrRecord;
    RC rc;
    vector<AttrInfo> ret;
    bool hit=false;
    attrScan.OpenScan(attrcatHandler,AttrType::STRING,MAXNAME+1,
                     offsetof(AttrInfo,attrName), CompOp::NO_OP, nullptr);
    while (attrScan.GetNextRec(attrRecord) != RM_EOF)
    {
        char *attrData;
        attrRecord.GetData(attrData);
        ret.push_back(*(AttrInfo *) attrData);
    }
    return ret;
}

void SM_Manager::flush()
{
    printer->flush();
}

RC SM_Manager::relExist(std::string relName)
{
    assert(isOpen);
    RM_FileScan relScan;
    RM_Record relRecord;
    relScan.OpenScan(relcatHandler, AttrType::STRING, relName.length() + 1,
                     offsetof(RelationMeta, relName), CompOp::EQ_OP, relName.c_str());
    if (relScan.GetNextRec(relRecord)!=RM_EOF)
    {
        relScan.CloseScan();
        return 1;
    }
    relScan.CloseScan();
    return 0;
}

RC SM_Manager::relExist(vector<std::string> relNames)
{
    assert(isOpen);
    for (auto relName : relNames)
    {
        if (relExist(relName)==0)
            return 0;
    }
    return 1;
}

RC SM_Manager::relGet(std::string relName, struct RelationMeta *relmeta)
{
    assert(isOpen);
    RM_FileScan relScan;
    RM_Record relRecord;
    char *data;

    relScan.OpenScan(relcatHandler,
                     AttrType::STRING,
                     relName.length() + 1,
                     offsetof(RelationMeta, relName),
                     CompOp::EQ_OP,
                     relName.c_str());

    if (relScan.GetNextRec(relRecord) != RM_EOF)
    {
        relRecord.GetData(data);
        memcpy(relmeta, data, sizeof (RelationMeta));
        relScan.CloseScan();
        return 0;
    }

    relScan.CloseScan();
    return 1;
}

RC SM_Manager::attrExist(RelAttrType attrName)
{
    assert(isOpen);
    RM_FileScan attrScan;
    RM_Record attrRecord;
    char * pData;
    attrScan.OpenScan(attrcatHandler, AttrType::STRING, attrName.first.length() + 1,
                      offsetof(AttrInfo, relName),
                      CompOp::EQ_OP, (void *) (attrName.first.c_str()));
    while (attrScan.GetNextRec(attrRecord) != RM_EOF)
    {
        attrRecord.GetData(pData);
        // scan中保证了relName一致，以下判断attrName一致
        if (strcmp(((AttrInfo *) pData)->attrName, attrName.second.c_str()) == 0)
        {

            attrScan.CloseScan();
            return 1;
        }
    }
    attrScan.CloseScan();
    return 0;
}

RC SM_Manager::attrExist(vector<RelAttrType> attrNames)
{
    assert(isOpen);
    for (auto attrName:attrNames)
    {
        if (!attrExist(attrName))
            return 0;
    }
    return 1;
}

RC SM_Manager::attrGet(RelAttrType attrName, AttrInfo* attrInfo)
{
    assert(isOpen);
    RM_FileScan attrScan;
    RM_Record attrRecord;
    char * pData;
    attrScan.OpenScan(attrcatHandler, AttrType::STRING, attrName.first.length() + 1,
                      offsetof(AttrInfo, relName),
                      CompOp::EQ_OP, (void *) (attrName.first.c_str()));
    while (attrScan.GetNextRec(attrRecord) != RM_EOF)
    {
        attrRecord.GetData(pData);
        // scan中保证了relName一致，以下判断attrName一致
        if (strcmp(((AttrInfo *) pData)->attrName, attrName.second.c_str()) == 0)
        {
            memcpy(attrInfo, pData, sizeof(AttrInfo));
            attrScan.CloseScan();
            return 0;
        }
    }
    attrScan.CloseScan();
    return 1;
}

/**
 *
 * @param relName
 * @return
 * @todo sort the attr against offset
 */
vector<AttrInfo> SM_Manager::attrGet(std::string relName)
{
    assert(isOpen);

    vector<AttrInfo> attributes;
    RM_FileScan attrScan;
    RM_Record attrRecord;
    AttrInfo attr;
    char * pData;

    attrScan.OpenScan(attrcatHandler,
                      AttrType::STRING,
                      MAXNAME+1,
                      offsetof(AttrInfo, relName),
                      CompOp::EQ_OP,
                      (void *) (relName.c_str()));

    while (attrScan.GetNextRec(attrRecord) != RM_EOF)
    {
        attrRecord.GetData(pData);
        memcpy(&attr, pData, sizeof(AttrInfo));
        attributes.push_back(attr);
    }

    attrScan.CloseScan();
    return attributes;
}

RC SM_Manager::attrRefresh(std::string relName, std::string attrName, AttrInfo *attr)
{
    assert(isOpen);

    RM_FileScan attrScan;
    RM_Record attrRecord;
    char * pData;

    attrScan.OpenScan(attrcatHandler,
                      AttrType::STRING,
                      MAXNAME+1,
                      offsetof(AttrInfo, relName),
                      CompOp::EQ_OP,
                      (void *) (relName.c_str()));

    while (attrScan.GetNextRec(attrRecord) != RM_EOF)
    {
        attrRecord.GetData(pData);
        if(strcmp(((AttrInfo*)pData)->attrName, attrName.c_str())) continue;
        memcpy(pData, attr, sizeof(AttrInfo));
        attrcatHandler.UpdateRec(attrRecord);
        break;
    }

    attrScan.CloseScan();

    return 0;
}

RM_FileHandle SM_Manager::filehandleGet(std::string relName)
{
    auto it = smFileHandle.find(relName);

    if(it == smFileHandle.end())
    {
        // the file do not exist in handler yet.
        RM_FileHandle newhandle;
        rmm->OpenFile(relToFileName(relName).data(), newhandle);
        smFileHandle.insert(std::make_pair(relName, newhandle));
        return newhandle;
    }

    return it->second;
}

IX_IndexHandle* SM_Manager::indexhandleGet(std::string relName, int index)
{
    std::string indexName = getFileNameWithIndex(relName, index);

    auto it = ixIndexHandle.find(indexName);

    if(it == ixIndexHandle.end())
    {
        IX_IndexHandle *newhandle;
        newhandle = new IX_IndexHandle();
        ixm->OpenIndex(relName.c_str(), index, *newhandle);
        ixIndexHandle.insert(std::make_pair(indexName, newhandle));
        return newhandle;
    }

    return it->second;
}

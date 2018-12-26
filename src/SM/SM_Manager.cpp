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
    cerr << "Opening DB : " << dbName << endl;
    if (strcmp(dbName, RELCAT) == 0 || strcmp(dbName, ATTRCAT) == 0)
    {
        return SM_INVALID_DB_NAME;
    }

    assert(getcwd(initialCwd, 2048));
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

    RM_FileScan relScan;
    RM_Record relRecord;
    relScan.OpenScan(relcatHandler, AttrType::STRING, strlen(relName) + 1,
                     offsetof(RelationMeta, relName), CompOp::EQ_OP, relName);
    if (relScan.GetNextRec(relRecord)!=RM_EOF)
    {
        printer->getSS()<<"Same name database exists\n";
        relScan.CloseScan();
        return SM_TABLE_EXIST;
    }
    relScan.CloseScan();

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
    RM_FileScan relScan;
    RM_Record relRecord;
    bool hit=false;
    relScan.OpenScan(relcatHandler,AttrType::STRING,MAXNAME+1,
            offsetof(RelationMeta,relName), CompOp::EQ_OP, (void *)relName);
    while (relScan.GetNextRec(relRecord)!=RM_EOF)
    {
        hit=true;
        RID rid;
        relRecord.GetRid(rid);
        rc=relcatHandler.DeleteRec(rid);
        assert(rc==0);
        rc=rmm->DestroyFile(relToFileName(relName).data());
        assert(rc==0);
        break;
    }
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

        // scan中保证了relName一致，以下判断attrName一致
        if (strcmp(((AttrInfo *) pData)->attrName, attrName) == 0)
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
    IX_IndexHandle ixIndexHandle;
    ixm->OpenIndex(relName, indexNum, ixIndexHandle);
    rmm->OpenFile(relToFileName(relName).data(),tableHandle);
    fileScan.OpenScan(tableHandle, attrInfo->attrType, attrInfo->attrLength,
                      attrInfo->offset, NO_OP, nullptr);
    // iterate entry and insert into indexHandler
    while (attrScan.GetNextRec(entryRecord) != RM_EOF)
    {
        char *tempData;
        RID rid;
        entryRecord.GetData(tempData);
        entryRecord.GetRid(rid);
        ixIndexHandle.InsertEntry(tempData + attrInfo->offset, rid);
    }
    ixIndexHandle.ForcePages();
    ixm->CloseIndex(ixIndexHandle);
    fileScan.CloseScan();
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
    hit=false;
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
            if (rc)
            {
                cerr << "Destory index error: " << rc << endl;
            }
            assert(rc==0);

            attrInfo->indexNum=0;
            attrcatHandler.UpdateRec(attrRecord);

            // No indexNum pool is maintained, so there is no reduction
            // update rel
//            relScan.OpenScan(relcatHandler,AttrType::STRING,strlen(relName)+1,
//                    offsetof(RelationMeta,relName), EQ_OP, relName);
//            bool hit=false;
//            while (relScan.GetNextRec(relRecord)!=RM_EOF)
//            {
//                hit=true;
//                break;
//            }
//            assert(hit);
//            char *relData;
//            relRecord.GetData(relData);
//            ((RelationMeta*)relData)->indexCount--;
//            relcatHandler.UpdateRec(relRecord);
            // No indexNum pool is maintained, so there is no reduction

            hit = true;
            break;
        }
    }
    attrScan.CloseScan();
    if (!hit)
        return SM_NONEXIST_RELATION;
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
    RM_FileScan relScan;
    RM_Record relRecord;
    RC rc;
    bool hit=false;
    relScan.OpenScan(relcatHandler,AttrType::STRING,MAXNAME+1,
                     offsetof(RelationMeta,relName), CompOp::NO_OP, nullptr);
    while (relScan.GetNextRec(relRecord) != RM_EOF)
    {
        char *relationMetaData;
        relRecord.GetData(relationMetaData);
        printer->PrintTables((RelationMeta *) relationMetaData, 1);
    }
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
//        printer->PrintTables((RelationMeta *) relationMetaData, 1);
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

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
    RelationMeta relationMeta;
    for (int i=0;i<attrCount;++i)
    {
        if (nameSet.find(string(attributes[i].attrName))!=nameSet.end())
            return SM_SAME_NAME_ATTR;
        nameSet.insert(string(attributes[i].attrName));
        attributes[i].offset = relSize;
        strcpy(attributes[i].relName, relName);
        relSize += attributes[i].attrLength;
    }
    relationMeta.attrCount=attrCount;
    relationMeta.indexCount=0;
    strcpy(relationMeta.relName,relName);
    relationMeta.tupleLength=relSize;

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
    return 0;
}


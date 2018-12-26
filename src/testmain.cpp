//
// Created by 杨乐 on 2018/11/5.
//

#include "PF_Test/pftest.h"
#include "RM_Test/rmtest.h"
#include "IX_Test/ixtest.h"
#include "SM/SM_PUBLIC.h"
#include "Parser/astree.h"

int main(int argc, char *argv[])
{

//    FileManager fm;
//    BufPageManager bpm(&fm);
//    RM_Manager rmm(&fm, &bpm);
//    IX_Manager ixm(fm,bpm);
//    SM_Manager sm(ixm,rmm);
//    // never use a short and normal name as test directory
//    char dbName[]="testDbapboa";
//    char attrName[]="attr1";
//    char relName[]="rel1";
//    sm.CreateDb(dbName);
//    sm.OpenDb(dbName);
//    AttrInfo attrInfo[5];
//    attrInfo->attrLength=4;
//    attrInfo->attrType=AttrType::INT;
//    strcpy(attrInfo->attrName, attrName);
//    attrInfo->flag=0;
//    sm.CreateTable(relName,1,attrInfo);
////    testing::internal::CaptureStdout();
//    sm.PrintTables();
//    auto tables=sm.TestReturnTables();
//    printf("Size = %d\n", tables.size());
//    sm.CloseDb();

    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager);
    QL_Manager qlManager(smManager, ixManager, rmManager);

    std::cerr << "Before Test." << std::endl;
    treeparser(smManager, qlManager);


    return 0;
}
//
// Created by eric on 18-12-23.
//

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <gtest/gtest.h>
#include <vector>
#include "../SM/SM_PRIVATE.h"
#include "../Parser/astree.h"
using namespace std;

class SM : public ::testing::Test {
protected:
    char initialCwd[2049];
    void SetUp () override{
        char dbName[]="testDbapboa";
        char dbName2[]="asdfasfeawef";
        system("rm -r testDbapboa");
        system("rm -r asdfasfeawef");

        ASSERT_EQ(initialCwd, getcwd(initialCwd, 2048));
        clearParser();
    }

    void TearDown () override{
        ASSERT_EQ(0, chdir(initialCwd));
        clearParser();
    }
};


TEST_F(SM, CreateDb)
{
    FileManager fm;
    BufPageManager bpm(&fm);
    RM_Manager rmm(&fm, &bpm);
    IX_Manager ixm(fm,bpm);
    SM_Manager sm(ixm,rmm);
    // never use a short and normal name as test directory
    char dbName[]="testDbapboa";
    char dbName2[]="asdfasfeawef";
//    system("rm -r testDbapboa");
//    system("rm -r asdfasfeawef");
//    // clean up
//    sm.DestroyDb(dbName);
//    sm.DestroyDb(dbName2);

    ASSERT_EQ(0, sm.CreateDb(dbName));
    ASSERT_EQ(SM_SYSCALL_ERROR, sm.CreateDb(dbName));
    ASSERT_EQ(0, sm.OpenDb(dbName));
    ASSERT_EQ(SM_DB_NOT_CLOSE, sm.CreateDb( dbName2));
    ASSERT_EQ(0, sm.CloseDb());
    ASSERT_EQ(0, sm.CreateDb(dbName2));

    ASSERT_EQ(0, sm.DestroyDb(dbName));
    ASSERT_EQ(0, sm.DestroyDb(dbName2));
}

TEST_F(SM, CreateTable)
{
    FileManager fm;
    BufPageManager bpm(&fm);
    RM_Manager rmm(&fm, &bpm);
    IX_Manager ixm(fm,bpm);
    SM_Manager sm(ixm,rmm);
    // never use a short and normal name as test directory
    char dbName[]="testDbapboa";
    char attrName[]="attr1";
    char relName[]="rel1";
    ASSERT_EQ(0, sm.CreateDb(dbName));
    ASSERT_EQ(0, sm.OpenDb(dbName));
    AttrInfo attrInfo[5];
    attrInfo->attrLength=4;
    attrInfo->attrType=AttrType::INT;
    strcpy(attrInfo->attrName, attrName);
    attrInfo->flag=0;
    ASSERT_EQ(0, sm.CreateTable(relName,1,attrInfo));
//    testing::internal::CaptureStdout();
    ASSERT_EQ(0, sm.PrintTables());
    auto tables=sm.TestReturnTables();
    ASSERT_EQ(1, tables.size());
    EXPECT_STREQ(relName,tables[0].relName);
    EXPECT_EQ(1,tables[0].attrCount);
    EXPECT_EQ(0,tables[0].indexCount);

    auto attrs=sm.TestReturnAttrs();
    EXPECT_EQ(1, attrs.size());
    EXPECT_STREQ(attrName, attrs[0].attrName);
    EXPECT_STREQ(relName, attrs[0].relName);
    EXPECT_EQ(0, attrs[0].indexNum);

    ASSERT_EQ(0, sm.CreateIndex("rel1", "attr1"));
    tables=sm.TestReturnTables();
    EXPECT_EQ(1, tables.size());
    EXPECT_STREQ(relName,tables[0].relName);
    EXPECT_EQ(1,tables[0].attrCount);
    EXPECT_EQ(1,tables[0].indexCount)<<"Have created an index.";

    attrs=sm.TestReturnAttrs();
    EXPECT_EQ(1, attrs.size());
    EXPECT_STREQ(attrName, attrs[0].attrName);
    EXPECT_STREQ(relName, attrs[0].relName);
    EXPECT_EQ(1, attrs[0].indexNum);

    ASSERT_EQ(0, sm.DropIndex("rel1", "attr1"));
    tables=sm.TestReturnTables();
    EXPECT_EQ(1, tables.size());
    EXPECT_STREQ(relName,tables[0].relName);
    EXPECT_EQ(1,tables[0].attrCount);
    EXPECT_EQ(1,tables[0].indexCount)<<"Destroy an index. But cnt should "
                                       "be monotonous.";

    attrs=sm.TestReturnAttrs();
    EXPECT_EQ(1, attrs.size());
    EXPECT_STREQ(attrName, attrs[0].attrName);
    EXPECT_STREQ(relName, attrs[0].relName);
    EXPECT_EQ(0, attrs[0].indexNum)<<"Destroy an index should change the indexNum.";

    ASSERT_EQ(0, sm.DropTable("rel1"));
    tables=sm.TestReturnTables();
    EXPECT_EQ(0, tables.size());
}

TEST_F(SM, Exist)
{
    FileManager fm;
    BufPageManager bpm(&fm);
    RM_Manager rmm(&fm, &bpm);
    IX_Manager ixm(fm,bpm);
    SM_Manager sm(ixm,rmm);
    // never use a short and normal name as test directory
    char dbName[]="testDbapboa";
    char attrName[]="attr1";
    char relName[]="rel1";
    string relNameString = relName;
    string attrNameString = attrName;
    vector<string> relV, relVMore;
    relV.push_back(relNameString);
    relVMore.push_back(relNameString);
    relVMore.push_back("aa123");
    vector<RelAttrType> attrV, attrVMore, attrVNull;
    attrV.push_back(make_pair(relNameString, attrNameString));
    attrVMore.push_back(make_pair(relNameString, attrNameString));
    attrVMore.push_back(make_pair(relNameString, "zj43"));

    ASSERT_EQ(0, sm.CreateDb(dbName));
    ASSERT_EQ(0, sm.OpenDb(dbName));
    AttrInfo attrInfo[5];
    attrInfo->attrLength=4;
    attrInfo->attrType=AttrType::INT;
    strcpy(attrInfo->attrName, attrName);
    attrInfo->flag=0;
    ASSERT_EQ(0, sm.CreateTable(relName,1,attrInfo));
    ASSERT_EQ(0, sm.PrintTables());
    EXPECT_EQ(1, sm.relExist(relNameString));
    EXPECT_EQ(1, sm.relExist(relV));
    EXPECT_EQ(0, sm.relExist(relVMore));
    EXPECT_EQ(1, sm.attrExist(make_pair(relNameString, attrNameString)));
    EXPECT_EQ(1, sm.attrExist(attrV));
    EXPECT_EQ(0, sm.attrExist(attrVMore));
    EXPECT_EQ(1, sm.attrExist(attrVNull));

    ASSERT_EQ(0, sm.DropTable("rel1"));
    EXPECT_EQ(0, sm.relExist(relNameString));
    EXPECT_EQ(0, sm.relExist(relV));
}

TEST_F(SM, PersistentCreateTable)
{
    FileManager fm;
    BufPageManager bpm(&fm);
    RM_Manager rmm(&fm, &bpm);
    IX_Manager ixm(fm,bpm);
    SM_Manager sm(ixm,rmm);
    // never use a short and normal name as test directory
    char dbName[]="testDbapboa";
    char attrName[]="attr1";
    char relName[]="rel1";
    ASSERT_EQ(0, sm.CreateDb(dbName));
    ASSERT_EQ(0, sm.OpenDb(dbName));
    AttrInfo attrInfo[5];
    attrInfo->attrLength=4;
    attrInfo->attrType=AttrType::INT;
    strcpy(attrInfo->attrName, attrName);
    attrInfo->flag=0;
    ASSERT_EQ(0, sm.CreateTable(relName,1,attrInfo));
//    testing::internal::CaptureStdout();
    ASSERT_EQ(0, sm.PrintTables());
    auto tables=sm.TestReturnTables();
    EXPECT_EQ(1, tables.size());
    EXPECT_STREQ(relName,tables[0].relName);
    EXPECT_EQ(1,tables[0].attrCount);
    EXPECT_EQ(0,tables[0].indexCount);

    auto attrs=sm.TestReturnAttrs();
    EXPECT_EQ(1, attrs.size());
    EXPECT_STREQ(attrName, attrs[0].attrName);
    EXPECT_STREQ(relName, attrs[0].relName);
    EXPECT_EQ(0, attrs[0].indexNum);

    ASSERT_EQ(0, sm.CreateIndex("rel1", "attr1"));
    tables=sm.TestReturnTables();
    EXPECT_EQ(1, tables.size());
    EXPECT_STREQ(relName,tables[0].relName);
    EXPECT_EQ(1,tables[0].attrCount);
    EXPECT_EQ(1,tables[0].indexCount)<<"Have created an index.";

    attrs=sm.TestReturnAttrs();
    EXPECT_EQ(1, attrs.size());
    EXPECT_STREQ(attrName, attrs[0].attrName);
    EXPECT_STREQ(relName, attrs[0].relName);
    EXPECT_EQ(1, attrs[0].indexNum);

    // reopen
    sm.CloseDb();
    ASSERT_EQ(0, sm.OpenDb(dbName));
    tables=sm.TestReturnTables();
    EXPECT_EQ(1, tables.size());
    EXPECT_STREQ(relName,tables[0].relName);
    EXPECT_EQ(1,tables[0].attrCount);
    EXPECT_EQ(1,tables[0].indexCount)<<"Have created an index.";
    attrs=sm.TestReturnAttrs();
    EXPECT_EQ(1, attrs.size());
    EXPECT_STREQ(attrName, attrs[0].attrName);
    EXPECT_STREQ(relName, attrs[0].relName);
    EXPECT_EQ(1, attrs[0].indexNum);

    // drop
    ASSERT_EQ(0, sm.DropIndex("rel1", "attr1"));
    tables=sm.TestReturnTables();
    EXPECT_EQ(1, tables.size());
    EXPECT_STREQ(relName,tables[0].relName);
    EXPECT_EQ(1,tables[0].attrCount);
    EXPECT_EQ(1,tables[0].indexCount)<<"Destroy an index. But cnt should "
                                       "be monotonous.";

    attrs=sm.TestReturnAttrs();
    EXPECT_EQ(1, attrs.size());
    EXPECT_STREQ(attrName, attrs[0].attrName);
    EXPECT_STREQ(relName, attrs[0].relName);
    EXPECT_EQ(0, attrs[0].indexNum)<<"Destroy an index should change the indexNum.";

    ASSERT_EQ(0, sm.DropTable("rel1"));
    tables=sm.TestReturnTables();
    EXPECT_EQ(0, tables.size());
}

class SM_Parser : public ::testing::Test {
protected:
    char initialCwd[2049];
    int saveStdin;
    SM_Parser()
    {
//        saveStdin=dup(STDIN_FILENO);
    }

    void SetUp() override{
        char dbName[]="testDbapboa";
        char dbName2[]="asdfasfeawef";
        system("rm -r testDbapboa");
        system("rm -r asdfasfeawef");

        ASSERT_EQ(initialCwd, getcwd(initialCwd, 2048));
    }

    void TearDown() override{
        ASSERT_EQ(0, chdir(initialCwd));
        clearParser();
//        fflush(stdin);
//        fclose(stdin);
//        stdin = fdopen(saveStdin, "r");
    }
};

TEST_F(SM_Parser, CreateDB)
{
//    freopen("../src/gtestcase/dbstmt_test.txt","r",stdin);
//    StdoutPrinter printer;
//    FileManager* fm = new FileManager();
//    BufPageManager* bpm = new BufPageManager(fm);
//    RM_Manager rmManager(fm, bpm);
//    IX_Manager ixManager(*fm, *bpm);
//    SM_Manager smManager(ixManager, rmManager, &printer);
//    QL_Manager qlManager(smManager, ixManager, rmManager, &printer);
//
//    //std::cerr << "Before Test." << std::endl;
//    treeparser(smManager, qlManager);
//    //std::cerr << "Test Finished." << std::endl;
}

TEST_F(SM_Parser, CreateTalbes)
{
    freopen("../src/gtestcase/SM_Parser1.in","r",stdin);
    StdoutPrinter printer;
    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager, &printer);
    QL_Manager qlManager(smManager, ixManager, rmManager, &printer);

    //std::cerr << "Before Test." << std::endl;
    treeparser(smManager, qlManager);
    //std::cerr << "Test Finished." << std::endl;
}

TEST_F(SM_Parser, CreateTalbes_large)
{
    freopen("../src/gtestcase/SM_Parser2.in","r",stdin);
    StdoutPrinter printer;
    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager, &printer);
    QL_Manager qlManager(smManager, ixManager, rmManager, &printer);

    //std::cerr << "Before Test." << std::endl;
    treeparser(smManager, qlManager);
    //std::cerr << "Test Finished." << std::endl;
}

TEST_F(SM_Parser, CreateTalbes_large_persistent)
{
//    freopen("../src/gtestcase/SM_Parser3_1.in","r",stdin);
//    FileManager* fm = new FileManager();
//    BufPageManager* bpm = new BufPageManager(fm);
//
//    {
//        RM_Manager rmManager(fm, bpm);
//        IX_Manager ixManager(*fm, *bpm);
//        SM_Manager smManager(ixManager, rmManager);
//        QL_Manager qlManager(smManager, ixManager, rmManager);
//        std::cerr << "Before Test." << std::endl;
//        treeparser(smManager, qlManager);
//    clearParser();
//    smManager.CloseDb();
//    smManager.flush();
//        bpm->close();
//    }
//    {
//        RM_Manager rmManager(fm, bpm);
//        IX_Manager ixManager(*fm, *bpm);
//        SM_Manager smManager(ixManager, rmManager);
//        QL_Manager qlManager(smManager, ixManager, rmManager);
//        freopen("../src/gtestcase/SM_Parser3_2.in", "r", stdin);
//        treeparser(smManager, qlManager);
//        smManager.flush();
//        smManager.CloseDb();
//        bpm->close();
//    }
//    {
//        RM_Manager rmManager(fm, bpm);
//        IX_Manager ixManager(*fm, *bpm);
//        SM_Manager smManager(ixManager, rmManager);
//        QL_Manager qlManager(smManager, ixManager, rmManager);
//        freopen("../src/gtestcase/SM_Parser3_3.in", "r", stdin);
//        treeparser(smManager, qlManager);
//        smManager.flush();
//        smManager.CloseDb();
//        bpm->close();
//    }
//    std::cerr << "Test Finished." << std::endl;
}

//
// Created by eric on 18-12-23.
//

#include <algorithm>
#include <gtest/gtest.h>
#include "../SM/SM_PRIVATE.h"

class SM : public ::testing::Test {
protected:
    char initialCwd[2049];
    virtual void SetUp() {
        char dbName[]="testDbapboa";
        char dbName2[]="asdfasfeawef";
        system("rm -r testDbapboa");
        system("rm -r asdfasfeawef");

        ASSERT_EQ(initialCwd, getcwd(initialCwd, 2048));
    }

    virtual void TearDown() {
        ASSERT_EQ(0, chdir(initialCwd));
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

    ASSERT_EQ(0, sm.DropIndex("rel1", "attr1"));
    tables=sm.TestReturnTables();
    EXPECT_EQ(1, tables.size());
    EXPECT_STREQ(relName,tables[0].relName);
    EXPECT_EQ(1,tables[0].attrCount);
    EXPECT_EQ(1,tables[0].indexCount)<<"Destroy an index. But cnt should be monotonous.";

    attrs=sm.TestReturnAttrs();
    EXPECT_EQ(1, attrs.size());
    EXPECT_STREQ(attrName, attrs[0].attrName);
    EXPECT_STREQ(relName, attrs[0].relName);
    EXPECT_EQ(0, attrs[0].indexNum)<<"Destroy an index should change the indexNum.";

    ASSERT_EQ(0, sm.DropTable("rel1"));
    tables=sm.TestReturnTables();
    EXPECT_EQ(0, tables.size());
}

//TEST_F(SM, InsertData)
//{
//    FileManager fm;
//    BufPageManager bpm(&fm);
//    RM_Manager rmm(&fm, &bpm);
//    IX_Manager ixm(fm,bpm);
//    SM_Manager sm(ixm,rmm);
//    // never use a short and normal name as test directory
//    char dbName[]="testDbapboa";
//    char attrName[]="attr1";
//    ASSERT_EQ(0, sm.CreateDb(dbName));
//    ASSERT_EQ(0, sm.OpenDb(dbName));
//    AttrInfo attrInfo[5];
//    attrInfo->attrLength=4;
//    attrInfo->attrType=AttrType::INT;
//    strcpy(attrInfo->attrName, attrName);
//    attrInfo->flag=0;
//    ASSERT_EQ(0, sm.CreateTable("rel1",1,attrInfo));
//    ASSERT_EQ(0, sm.CreateIndex("rel1", "attr1"));
//    ASSERT_EQ(0, sm.DropIndex("rel1", "attr1"));
//    ASSERT_EQ(0, sm.DropTable("rel1"));
//}
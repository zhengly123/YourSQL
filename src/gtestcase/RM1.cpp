//
// Created by eric on 18-12-23.
//

#include <algorithm>
#include <gtest/gtest.h>
#include "../RM/rm.h"

class RM : public ::testing::Test {
protected:
    const char* filename="RMTestFile";
    virtual void SetUp() {
        system("rm RMTestFile");
    }

    virtual void TearDown() {
    }
};


TEST_F(RM, ViolateReadWrite)
{
    FileManager *fm;
    BufPageManager *bpm;
    RM_Manager *rmm;

    fm = new FileManager();
    bpm = new BufPageManager(fm);
    rmm = new RM_Manager(fm, bpm);

    rmm->CreateFile(filename, 32);

    RM_FileHandle test1;

    rmm->OpenFile(filename, test1);

    int data1 = 12345;
    char *p = (char*)&data1;
//    printf("Data(Written) = %d\n", *((int*)p));
    RID rid1;
    test1.InsertRec(p, rid1);

    RM_Record rec1;
    test1.GetRec(rid1, rec1);

    char *dat;
    rec1.GetData(dat);

//    printf("Data = %d\n", *((int*)dat));
    EXPECT_EQ(12345, *((int *) dat));

    *((int*)dat) = 23456;

    //rec1.SetData(dat); // 无需SetData；SetData是为内部提供的接口；只需要对dat进行修改即可

    test1.UpdateRec(rec1);

    test1.GetRec(rid1, rec1);
    rec1.GetData(dat);
//    printf("Data(Updated) = %d\n", *((int*)dat));
    EXPECT_EQ(23456, *((int *) dat));
}

TEST_F(RM, PersistentReadWrite)
{
    FileManager *fm;
    BufPageManager *bpm;
    RM_Manager *rmm;

    fm = new FileManager();
    bpm = new BufPageManager(fm);
    rmm = new RM_Manager(fm, bpm);

    rmm->CreateFile(filename, 32);

    RM_FileHandle test1;

    rmm->OpenFile(filename, test1);

    int data1 = 12345;
    char *p = (char*)&data1;
//    printf("Data(Written) = %d\n", *((int*)p));
    RID rid1;
    test1.InsertRec(p, rid1);
    int fileId;
    test1.GetID(fileId);
    rmm->CloseFile(test1);

    RM_FileHandle test2;
    rmm->OpenFile(filename, test2);
    RM_Record rec1;
    test1.GetRec(rid1, rec1);

    char *dat;
    rec1.GetData(dat);
//    printf("Data = %d\n", *((int*)dat));
    EXPECT_EQ(12345, *((int *) dat));
}

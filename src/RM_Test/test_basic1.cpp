//
// Created by 杨乐 on 2018/11/25.
//

#include "rmtest.h"

// 测试：rmmannager的建立；记录的插入、修改及查询

void rm_test_basic1()
{
    FileManager *fm;
    BufPageManager *bpm;
    RM_Manager *rmm;

    fm = new FileManager();
    bpm = new BufPageManager(fm);
    rmm = new RM_Manager(fm, bpm);

    rmm->CreateFile("Test1", 32);

    RM_FileHandle test1;

    rmm->OpenFile("Test1", test1);

    int data1 = 12345;
    char *p = (char*)&data1;
    printf("Data(Written) = %d\n", *((int*)p));
    RID rid1;
    test1.InsertRec(p, rid1);

    RM_Record rec1;
    test1.GetRec(rid1, rec1);

    char *dat;
    rec1.GetData(dat);

    printf("Data = %d\n", *((int*)dat));

    *((int*)dat) = 23456;

    //rec1.SetData(dat); // 无需SetData；SetData是为内部提供的接口；只需要对dat进行修改即可

    test1.UpdateRec(rec1);

    test1.GetRec(rid1, rec1);
    rec1.GetData(dat);
    printf("Data(Updated) = %d\n", *((int*)dat));

}

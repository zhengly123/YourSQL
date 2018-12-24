//
// Created by eric on 18-12-18.
//

#include <algorithm>
#include <gtest/gtest.h>
#include "../IX/IX_PRIVATE.h"

TEST(IX, Mixture)
{
    MyBitMap::initConst();   //新加的初始化
//    for(int i = 0; i < 61; ++ i)
//        cout << hmap[i]<< ",";
//    cout << endl;

    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    IX_Manager ixManager(*fm,*bpm);
    IX_IndexHandle ixIndexHandle;

    // Reload test
//    ixManager.OpenIndex("a",1,ixIndexHandle);
//    ixIndexHandle.printBPT();
//    ixIndexHandle.printLinearLeaves();
//    return;

    ixManager.CreateIndex("a", 1, AttrType::INT, 4);
    ixManager.OpenIndex("a",1,ixIndexHandle);
//    ixIndexHandle.printBPT();
//    ixIndexHandle.printLinearLeaves();
    int a[1000]={0,1,1,7,8,7,0,3,4,5,6};
    for (int i=0;i<10;++i)
    {
//        printf("===========insert %d===========\n", i);
        a[i] = i;
        ASSERT_EQ(0, ixIndexHandle.InsertEntry(a+i,RID(0,i)));
//        ixIndexHandle.printBPT();
//        ixIndexHandle.printLinearLeaves();
    }
    for (int i=0;i<10;++i)
    {
//        printf("===========delete %d===========\n", i);
        a[i] = i;
        ASSERT_EQ(0, ixIndexHandle.DeleteEntry(a+i,RID(0,i)));
//        ixIndexHandle.printBPT();
//        ixIndexHandle.printLinearLeaves();
    }

    a[1]=1;
    for (int i=0;i<50;++i)
    {
//        printf("===========duplicate insert %d===========\n", i);
//        a[i] = i;
        ASSERT_EQ(0, ixIndexHandle.InsertEntry(a + 1, RID(0, i)));
//        ixIndexHandle.printBPT();
//        ixIndexHandle.printLinearLeaves();
    }
    for (int i=0;i<50;++i)
    {
//        printf("===========duplicate delete %d===========\n", i);
//        a[i] = i;
        ASSERT_EQ(0,ixIndexHandle.DeleteEntry(a + 1, RID(0, i)));
//        ixIndexHandle.printBPT();
//        ixIndexHandle.printLinearLeaves();
    }

    for (int i=0;i<50;++i)
    {
//        printf("===========kv duplicate insert %d===========\n", i);
//        a[i] = i;
        ASSERT_EQ(0,ixIndexHandle.InsertEntry(a + 1, RID(0, 2)));
//        ixIndexHandle.printBPT();
//        ixIndexHandle.printLinearLeaves();
    }
    for (int i=0;i<1;++i)
    {
//        printf("===========kv duplicate delete %d===========\n", i);
//        a[i] = i;
        ASSERT_EQ(0,ixIndexHandle.DeleteEntry(a + 1, RID(0, 2)));
//        ixIndexHandle.printBPT();
//        ixIndexHandle.printLinearLeaves();
    }

    ixIndexHandle.ForcePages();
//    ixManager.CloseIndex(ixIndexHandle);
//    bpm->close();
//    fm->closeFile(file);
    int b[1000]={0,1,1,7,8,7,0,3,4,5,6};
    int c[1000] = {0, 6, 1, 2, 8, 9, 10, 3, 5, 4};
    for (int i=0;i<11;++i)
    {
//        printf("===========insert %d===========\n", i);
        ASSERT_EQ(0,ixIndexHandle.InsertEntry(b+i,RID(0,i)));
//        ixIndexHandle.printBPT();
//        ixIndexHandle.printLinearLeaves();
    }

    IX_IndexScan ixIndexScan;
    ixIndexScan.OpenScan(ixIndexHandle, NE_OP, b + 7);
    RID rid;
//    printf("===========scan===========\n");
//    ixIndexHandle.printLinearLeaves();
    int cnt=0;
    std::sort(b,b+10);
    while (ixIndexScan.GetNextEntry(rid)!=IX_ITERATOR_TO_END)
    {
        EXPECT_EQ(0,rid.GetPageNum());
        EXPECT_EQ(c[cnt++],rid.GetSlotNum());
//        printf("(%d,%d)->", rid.GetPageNum(), rid.GetSlotNum());
        fflush(stdout);
        ASSERT_LE(cnt,10);
    }
    ASSERT_EQ(cnt,10);
//    puts("");

    bpm->close();
    //程序结束前可以调用BufPageManager的某个函数将缓存中的内容写回
    //具体的函数大家可以看看ppt或者程序的注释
}
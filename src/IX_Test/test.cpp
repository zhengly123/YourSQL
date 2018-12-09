//
// Created by 杨乐 on 2018/11/25.
//

#include "ixtest.h"

void ix_test()
{
    MyBitMap::initConst();   //新加的初始化
    for(int i = 0; i < 61; ++ i)
        cout << hmap[i]<< ",";
    cout << endl;

    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    fm->createFile("testfile.txt"); //新建文件
    fm->createFile("testfile2.txt");
    int fileID, f2;
    fm->openFile("testfile.txt", fileID); //打开文件，fileID是返回的文件id
    fm->openFile("testfile2.txt", f2);
    IX_Manager ixManager(*fm,*bpm);
    IX_IndexHandle ixIndexHandle;
    ixManager.CreateIndex("a", 1, AttrType::INT, 4);
    ixManager.OpenIndex("a",1,ixIndexHandle);
    ixIndexHandle.printBPT();
    int a[1000]={0,1,1,7,8,7,0,3,4,5,6};
    for (int i=0;i<10;++i)
    {
        printf("===========insert %d===========\n", i);
//        a[i] = i;
        ixIndexHandle.InsertEntry(a+i,RID(0,i));
        ixIndexHandle.printBPT();
        ixIndexHandle.printLinearLeaves();
    }
    for (int i=0;i<10;++i)
    {
        printf("===========delete %d===========\n", i);
//        a[i] = i;
        ixIndexHandle.DeleteEntry(a+i,RID(0,i));
        ixIndexHandle.printBPT();
        ixIndexHandle.printLinearLeaves();
    }



    bpm->close();
    //程序结束前可以调用BufPageManager的某个函数将缓存中的内容写回
    //具体的函数大家可以看看ppt或者程序的注释
}
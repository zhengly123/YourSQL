//
// Created by 杨乐 on 2018/11/25.
//

#include "pftest.h"

void pf_test()
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
    for (int pageID = 0; pageID < 1000; ++ pageID) {
        int index;
        //为pageID获取一个缓存页
        BufType b = bpm->allocPage(fileID, pageID, index, false);
        //注意，在allocPage或者getPage后，千万不要进行delete[] b这样的操作
        //内存的分配和管理都在BufPageManager中做好，不需要关心，如果自行释放会导致问题
        b[0] = pageID; //对缓存页进行写操作
        b[1] = fileID;
        bpm->markDirty(index); //标记脏页
        //在重新调用allocPage获取另一个页的数据时并没有将原先b指向的内存释放掉
        //因为内存管理都在BufPageManager中做好了
        b = bpm->allocPage(f2, pageID, index, false);
        b[0] = pageID;
        b[1] = f2;
        bpm->markDirty(index);
    }

    for (int pageID = 0; pageID < 1000; ++ pageID) {
        int index;
        //为pageID获取一个缓存页
        BufType b = bpm->getPage(fileID, pageID, index);
        //注意，在allocPage或者getPage后，千万不要进行delete[] b这样的操作
        //内存的分配和管理都在BufPageManager中做好，不需要关心，如果自行释放会导致问题
        cout << b[0] << ":" << b[1] << endl; 		//读取缓存页中第一个整数
        bpm->access(index); //标记访问
        b = bpm->getPage(f2, pageID, index);
        cout << b[0] << ":" << b[1] << endl;
        bpm->access(index);
    }
    cerr << fileID << " , " << f2 << endl;

    bpm->close();
    //程序结束前可以调用BufPageManager的某个函数将缓存中的内容写回
    //具体的函数大家可以看看ppt或者程序的注释
}
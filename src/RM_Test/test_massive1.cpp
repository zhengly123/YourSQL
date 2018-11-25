//
// Created by 杨乐 on 2018/11/25.
//

#include "rmtest.h"


void rm_test_massive1()
{
    // Manager initialize
    FileManager *fm;
    BufPageManager *bpm;
    RM_Manager *rmm;

    fm = new FileManager();
    bpm = new BufPageManager(fm);
    rmm = new RM_Manager(fm, bpm);

    // Each record contains 4 int
    rmm->CreateFile("TestMassive", 32 * 4);
    RM_FileHandle handle;
    rmm->OpenFile("TestMassive", handle);

    int G = 10;

    int data[4];

    RID rid;
    RM_Record rec;
    map<int, RID> ridmap;
    ridmap.clear();

    for(int i = 0; i < G; ++ i)
    {
        data[0] = i, data[1] = i * 2, data[2] = i * i, data[3] = - i;

        handle.InsertRec((char*)data, rid);
        ridmap.insert(make_pair(i, rid));
    }

    cerr << "Insertion complete , Cnt = " << G << endl;

    while(1)
    {
        int ty, x, y, z;
        cin >> ty;
        if(ty == -1) break;
        if(ty == 0) // query
        {
            cin >> x;
            if(ridmap.find(x) == ridmap.end())
            {
                cerr << "Index Error." << endl;
            }
            else
            {
                rid = ridmap[x];
                char *fetch;
                handle.GetRec(rid, rec);
                rec.GetData(fetch);
                int *fdata = (int*)fetch;
                cerr << "Fetching Data : " << endl;
                cerr << "  " << fdata[0] << "  " << fdata[1] <<"  " << fdata[2] <<"  " << fdata[3] << endl;
            }
        }
    }

    rmm->CloseFile(handle);
    bpm->close();
    fm->shutdown();
}
//
// Created by 杨乐 on 2018/12/24.
//

#include "rmtest.h"
#include <cmath>

struct testrec
{
    char ts[20];
    int ti;
    float tf;
};

void test_scan()
{
    cerr << "Test scan ..." << endl;

    FileManager *fm;
    BufPageManager *bpm;
    RM_Manager *rmm;
    RM_FileHandle handler;
    RM_FileScan scanner;
    RM_Record rec;
    RID rid;

    fm = new FileManager();
    bpm = new BufPageManager(fm);
    rmm = new RM_Manager(fm, bpm);

    testrec ret;

    rmm->CreateFile("rmmscan.txt", sizeof(testrec));
    rmm->OpenFile("rmmscan.txt", handler);

    for(int i = 1; i < 11; ++ i)
    {
        sprintf(ret.ts, "a%d", i);
        ret.ti = i;
        ret.tf = sqrt(i);
        handler.InsertRec((char*) &ret, rid);
    }

    int p = 5;
    scanner.OpenScan(handler, INT, 4, 20, GE_OP, &p);

    int rc;
    for(rc = scanner.GetNextRec(rec); rc == 0; rc = scanner.GetNextRec(rec))
    {
        char* data;
        rec.GetData(data);
        testrec* trec = (testrec*) data;
        cerr << "Record : " << endl;
        cerr << "   Str : " << trec->ts << endl;
        cerr << "   Int : " << trec->ti << endl;
        cerr << "   Flt : " << trec->tf << endl;
    }

}

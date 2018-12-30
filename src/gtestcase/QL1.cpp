//
// Created by 杨乐 on 2018/12/27.
//

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "../Parser/astree.h"
#include "../QL/QL_PUBLIC.h"
using namespace std;

class QL_INS : public :: testing :: Test
{
protected:
    char initialCwd[2049];

    void SetUp () override
    {
        /*
        char dbName[]="testDbapboa";
        char dbName2[]="asdfasfeawef";
        system("rm -r testDbapboa");
        system("rm -r asdfasfeawef");
        */
        ASSERT_EQ(initialCwd, getcwd(initialCwd, 2048));
        clearParser();
    }

    void TearDown () override
    {
        ASSERT_EQ(0, chdir(initialCwd));
        clearParser();
    }
};

TEST_F(QL_INS, INS_RELERROR)
{
    printf("\nTesting : Insert Relation Error. \n");
    freopen("../src/QL_test/ins_relerr.txt", "r" , stdin);

    StdoutPrinter printer;
    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager, &printer);
    QL_Manager qlManager(smManager, ixManager, rmManager, &printer);

    int rc;

    for(int i = 0; i < 3; ++ i)
    {
        rc = treeparser(smManager, qlManager, 0);
        EXPECT_EQ(rc, 0);
    }

    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, QL_RELNOTEXIST);

    for(;;)
    {
        rc = treeparser(smManager, qlManager, 0);
        if(rc == PARSEREXIT) break;
        EXPECT_EQ(rc, 0);
    }
}

TEST_F(QL_INS, INS_SIZEERR)
{
    printf("\nTesting : Insert Invalid Size Error. \n");
    freopen("../src/QL_test/ins_sizeerr.txt", "r" , stdin);

    StdoutPrinter printer;
    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager, &printer);
    QL_Manager qlManager(smManager, ixManager, rmManager, &printer);

    int rc;

    for(int i = 0; i < 3; ++ i)
    {
        rc = treeparser(smManager, qlManager, 0);
        EXPECT_EQ(rc, 0);
    }

    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, QL_INVALIDSIZE);

    for(;;)
    {
        rc = treeparser(smManager, qlManager, 0);
        if(rc == PARSEREXIT) break;
        EXPECT_EQ(rc, 0);
    }
}


TEST_F(QL_INS, INS_STRTOOLONG)
{
    printf("\nTesting : Insert String too long Error. \n");
    freopen("../src/QL_test/ins_strtoolong.txt", "r" , stdin);

    StdoutPrinter printer;
    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager, &printer);
    QL_Manager qlManager(smManager, ixManager, rmManager, &printer);

    int rc;

    for(int i = 0; i < 3; ++ i)
    {
        rc = treeparser(smManager, qlManager, 0);
        EXPECT_EQ(rc, 0);
    }

    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, QL_STRTOOLONG);

    for(;;)
    {
        rc = treeparser(smManager, qlManager, 0);
        if(rc == PARSEREXIT) break;
        EXPECT_EQ(rc, 0);
    }
}

TEST_F(QL_INS, INS_TYPEMISMATCH)
{
    printf("\nTesting : Insert Type Mismatch Error. \n");
    freopen("../src/QL_test/ins_typemismatch.txt", "r" , stdin);

    StdoutPrinter printer;
    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager, &printer);
    QL_Manager qlManager(smManager, ixManager, rmManager, &printer);

    int rc;

    for(int i = 0; i < 3; ++ i)
    {
        rc = treeparser(smManager, qlManager, 0);
        EXPECT_EQ(rc, 0);
    }

    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, QL_TYPEUNMATCHED);

    for(;;)
    {
        rc = treeparser(smManager, qlManager, 0);
        if(rc == PARSEREXIT) break;
        EXPECT_EQ(rc, 0);
    }
}


TEST_F(QL_INS, INS_NOTNULLERR)
{
    printf("\nTesting : Insert Non-null Type Error. \n");
    freopen("../src/QL_test/ins_notnullerror.txt", "r" , stdin);

    StdoutPrinter printer;
    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager, &printer);
    QL_Manager qlManager(smManager, ixManager, rmManager, &printer);

    int rc;

    for(int i = 0; i < 3; ++ i)
    {
        rc = treeparser(smManager, qlManager, 0);
        EXPECT_EQ(rc, 0);
    }

    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, QL_ATTRNOTNULL);

    for(;;)
    {
        rc = treeparser(smManager, qlManager, 0);
        if(rc == PARSEREXIT) break;
        EXPECT_EQ(rc, 0);
    }
}

class QL_DEL : public :: testing :: Test
{
protected:
    char initialCwd[2049];

    void SetUp () override
    {
        char dbName[]="testDbapboa";
//        char dbName2[]="asdfasfeawef";
        system("rm -r db1");
//        system("rm -r asdfasfeawef");
        ASSERT_EQ(initialCwd, getcwd(initialCwd, 2048));
        clearParser();
    }

    void TearDown () override
    {
        ASSERT_EQ(0, chdir(initialCwd));
        clearParser();
    }
};

TEST_F(QL_DEL, DEL)
{
    freopen("../src/gtestcase/QL_DELETE3.in","r",stdin);

    Printer *printer=new StdoutPrinter;
    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager, printer); // add printer
    QL_Manager qlManager(smManager, ixManager, rmManager, printer);// add printer

    int rc;

    for(int i = 0; i < 4; ++ i)
    {
        rc = treeparser(smManager, qlManager, 0);
        EXPECT_EQ(rc, 0);
    }
    //show 1
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    auto type=vector<string>();
    type.push_back(string("INT"));
    type.push_back(string("INT"));
    string s;
    int t;
    for (int i = 0; i < 2; ++i)
    {
        printer->getSS()>>s;
        ASSERT_EQ(s,type[i]);
    }
    int a[6] = {1, 3, 0, 3, 3, 4};
    for (int i = 0; i < 6; ++i)
    {
        if (i == 2)
        {
            printer->getSS()>>s;
            EXPECT_EQ(string("NULL"), s);
            continue;
        }
        printer->getSS()>>t;
        EXPECT_EQ(t,a[i]);
    }
    //show 2
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    for (int i = 0; i < 2; ++i)
    {
        printer->getSS()>>s;
        ASSERT_EQ(s,type[i]);
    }
    for (int i = 2; i < 6; ++i)
    {
        if (i == 2)
        {
            printer->getSS()>>s;
            EXPECT_EQ(string("NULL"), s);
            continue;
        }
        printer->getSS()>>t;
        EXPECT_EQ(t,a[i]);
    }
    //show 3
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    for (int i = 0; i < 2; ++i)
    {
        printer->getSS()>>s;
        ASSERT_EQ(s,type[i]);
    }
    for (int i = 2; i < 6; ++i)
    {
        if (i == 2)
        {
            printer->getSS()>>s;
            EXPECT_EQ(string("NULL"), s);
            continue;
        }
        printer->getSS()>>t;
        EXPECT_EQ(t,a[i]);
    }
    //show 4
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    for (int i = 0; i < 2; ++i)
    {
        printer->getSS()>>s;
        ASSERT_EQ(s,type[i]);
    }
    for (int i = 4; i < 6; ++i)
    {
        if (i == 2)
        {
            printer->getSS()>>s;
            EXPECT_EQ(string("NULL"), s);
            continue;
        }
        printer->getSS()>>t;
        EXPECT_EQ(t,a[i]);
    }

    for(;;)
    {
        rc = treeparser(smManager, qlManager, 0);
        if(rc == PARSEREXIT) break;
        EXPECT_EQ(rc, 0);
    }
}

TEST_F(QL_DEL, UPD)
{
    freopen("../src/gtestcase/QL_UPDATE1.in","r",stdin);

    Printer *printer=new StdoutPrinter;
    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager, printer); // add printer
    QL_Manager qlManager(smManager, ixManager, rmManager, printer);// add printer

    int rc;

    for(int i = 0; i < 4; ++ i)
    {
        rc = treeparser(smManager, qlManager, 0);
        EXPECT_EQ(rc, 0);
    }
    //show 1
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    auto type=vector<string>();
    type.push_back(string("INT"));
    type.push_back(string("INT"));
    string s;
    int t;
    for (int i = 0; i < 2; ++i)
    {
        printer->getSS()>>s;
        ASSERT_EQ(s,type[i]);
    }
    int a[6] = {1, 3, 2, 4, 3, 5};
    for (int i = 0; i < 6; ++i)
    {
        printer->getSS()>>t;
        EXPECT_EQ(t,a[i]);
    }
    //show 2
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    for (int i = 0; i < 2; ++i)
    {
        printer->getSS()>>s;
        ASSERT_EQ(s,type[i]);
    }
    for (int i = 0; i < 6; ++i)
    {
        if (i == 0)
        {
            printer->getSS()>>s;
            EXPECT_EQ(string("NULL"), s);
            continue;
        }
        printer->getSS()>>t;
        EXPECT_EQ(t,a[i]);
    }
    //show 3
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    for (int i = 0; i < 2; ++i)
    {
        printer->getSS()>>s;
        ASSERT_EQ(s,type[i]);
    }
    a[2] = 123;
    for (int i = 0; i < 6; ++i)
    {
        if (i == 0)
        {
            printer->getSS()>>s;
            EXPECT_EQ(string("NULL"), s);
            continue;
        }
        printer->getSS()>>t;
        EXPECT_EQ(t,a[i]);
    }
    //show 4
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    for (int i = 0; i < 2; ++i)
    {
        printer->getSS()>>s;
        ASSERT_EQ(s,type[i]);
    }
    a[3] = 5;
    for (int i = 0; i < 6; ++i)
    {
        if (i == 0)
        {
            printer->getSS()>>s;
            EXPECT_EQ(string("NULL"), s);
            continue;
        }
        printer->getSS()>>t;
        EXPECT_EQ(t,a[i]);
    }
    //show 5
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    for (int i = 0; i < 2; ++i)
    {
        printer->getSS()>>s;
        ASSERT_EQ(s,type[i]);
    }
    for (int i = 0; i < 6; ++i)
    {
        if (i == 0 || i == 3 || i == 5)
        {
            printer->getSS() >> s;
            EXPECT_EQ(string("NULL"), s);
            continue;
        }
        printer->getSS()>>t;
        EXPECT_EQ(t,a[i]);
    }
    //show 6
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    rc = treeparser(smManager, qlManager, 0);
    EXPECT_EQ(rc, 0);
    for (int i = 0; i < 2; ++i)
    {
        printer->getSS()>>s;
        ASSERT_EQ(s,type[i]);
    }
    for (int i = 0; i < 6; ++i)
    {
        if (i == 0 || i == 3 || i == 5)
        {
            printer->getSS() >> s;
            EXPECT_EQ(string("NULL"), s);
            continue;
        }
        printer->getSS()>>t;
        EXPECT_EQ(t,a[i]);
    }

    for(;;)
    {
        rc = treeparser(smManager, qlManager, 0);
        if(rc == PARSEREXIT) break;
        EXPECT_EQ(rc, 0);
    }
}

class QL_StringCmp : public :: testing :: Test
{
protected:
    char initialCwd[2049];
void SetUp () override
    {
        char dbName[]="testDbapboa";
//        char dbName2[]="asdfasfeawef";
        system("rm -r db1");
//        system("rm -r asdfasfeawef");
        ASSERT_EQ(initialCwd, getcwd(initialCwd, 2048));
        clearParser();
    }

    std::string exec()
    {
        Printer *printer=new StdoutPrinter;
        FileManager* fm = new FileManager();
        BufPageManager* bpm = new BufPageManager(fm);
        RM_Manager rmManager(fm, bpm);
        IX_Manager ixManager(*fm, *bpm);
        SM_Manager smManager(ixManager, rmManager, printer); // add printer
        QL_Manager qlManager(smManager, ixManager, rmManager, printer);// add printer

        int rc;
        for(;;)
        {
            rc = treeparser(smManager, qlManager, 0);
            if(rc == PARSEREXIT) break;
            EXPECT_EQ(rc, 0);
        }
        return printer->getSS().str();
    }

    void check(ifstream& fin, const std::string os)
    {
        istringstream iss(os);
        string out,ans;
        int cnt = 0;
        do
        {
            iss >> out;
            fin >> ans;
            EXPECT_EQ(out, ans) << "Token " << cnt;
            cnt++;
        } while (iss || fin);
    }

    void TearDown () override
    {
        ASSERT_EQ(0, chdir(initialCwd));
        clearParser();
    }
};

TEST_F(QL_StringCmp, SELECT_SingleTable)
{
//    printf("\nTesting : Insert Non-null Type Error. \n");
    freopen("../src/gtestcase/QL_SELECT1.in","r",stdin);
    auto os = exec();
    ifstream fin("../src/gtestcase/QL_SELECT1.out");
//    freopen("../src/gtestcase/QL_SELECT1.out","r",stdin);
    check(fin, os);
}

TEST_F(QL_StringCmp, SELECT_DoubleTable)
{
//    printf("\nTesting : Insert Non-null Type Error. \n");
    freopen("../src/gtestcase/QL_SELECT2.in","r",stdin);
    auto os = exec();
    ifstream fin("../src/gtestcase/QL_SELECT2.out");
//    freopen("../src/gtestcase/QL_SELECT2.out","r",stdin);
    check(fin, os);
}

TEST_F(QL_StringCmp, SELECT_TripleTable)
{
//    printf("\nTesting : Insert Non-null Type Error. \n");
    freopen("../src/gtestcase/QL_SELECT3.in","r",stdin);
    auto os = exec();
    ifstream fin("../src/gtestcase/QL_SELECT3.out");
//    freopen("../src/gtestcase/QL_SELECT3.out","r",stdin);
    check(fin, os);
}

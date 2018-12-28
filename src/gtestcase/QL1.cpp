//
// Created by 杨乐 on 2018/12/27.
//

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <gtest/gtest.h>
#include <vector>
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

    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager);
    QL_Manager qlManager(smManager, ixManager, rmManager);

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

    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager);
    QL_Manager qlManager(smManager, ixManager, rmManager);

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

    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager);
    QL_Manager qlManager(smManager, ixManager, rmManager);

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

    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager);
    QL_Manager qlManager(smManager, ixManager, rmManager);

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

    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager);
    QL_Manager qlManager(smManager, ixManager, rmManager);

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






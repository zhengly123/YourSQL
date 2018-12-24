//
// Created by 杨乐 on 2018/11/5.
//

#include "PF_Test/pftest.h"
#include "RM_Test/rmtest.h"
#include "IX_Test/ixtest.h"
#include "SM/SM_PUBLIC.h"
#include "Parser/astree.h"

int main(int argc, char *argv[])
{

    //pf_test();
    //rm_test_basic1();
    //rm_test_error(argc, argv);
    // ix_test();

    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager);
    QL_Manager qlManager(smManager, ixManager, rmManager);

    std::cerr << "Before Test." << std::endl;
    treeparser(smManager, qlManager);

//    test_scan();

    return 0;
}
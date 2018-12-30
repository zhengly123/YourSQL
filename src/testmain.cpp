//
// Created by 杨乐 on 2018/11/5.
//

#include "PF_Test/pftest.h"
#include "RM_Test/rmtest.h"
#include "IX_Test/ixtest.h"
#include "SM/SM_PUBLIC.h"
#include "Parser/astree.h"
#include "QL/QL_PUBLIC.h"

int main(int argc, char *argv[])
{

    Printer *printer = new StdoutPrinter;
    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager, printer); // add printer
    QL_Manager qlManager(smManager, ixManager, rmManager, printer);// add printer

    freopen("QL_SELECT5.in", "r", stdin);

    int rc;
    for(;;)
    {
        rc = treeparser(smManager, qlManager, 0);
        if(rc == PARSEREXIT) break;

        if(rc != 0) printf("ERROR.\n");
        //else printf("NORMAL.\n");
        //EXPECT_EQ(rc, 0);
    }

    //cout << printer->getSS().str();

    return 0;
}
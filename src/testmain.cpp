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

    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager, stdoutPrinter); // add printer
    QL_Manager qlManager(smManager, ixManager, rmManager, stdoutPrinter);// add printer

    //freopen("QL_UPDATE1.in", "r", stdin);

    int rc;
    for(;;)
    {
        rc = treeparser(smManager, qlManager, 0);
        if(rc == PARSEREXIT) break;

/*
        switch(rc)
        {
            case SM_FOREIGN_NOTFOUND : printf("Foreign not found.\n"); break;
            case SM_FOREIGN_NOTPRIMARY : printf("Foreign key not primary.\n"); break;
            case PASERR_MULTIPLE_PRIMARY : printf("Multiple primary key.\n"); break;
            case PASERR_PRIMARY_NOTFOUND : printf("Primary Key not found.\n"); break;
            case PASERR_ATTR_TOOLONG : printf("Attr too long.\n"); break;
            case SM_SAME_NAME_ATTR : printf("Same name attr.\n"); break;
            case QL_PRIMARY_DUPLICATE : printf("Insertion : Primary duplicate.\n"); break;
            default:
                if(rc == 0) printf("Normal.\n");
                else printf("Unrecognized error.\n");
        }
*/

        //if(rc != 0) printf("ERROR.\n");
        //else printf("NORMAL.\n");
        //EXPECT_EQ(rc, 0);

#ifdef TERMMSG
        if(rc > 0) printf("ERROR: %s\n", errorGet(rc).c_str());
#endif
        // if(rc == 0) printf("NORMAL.\n");
    }

    //cout << printer->getSS().str();

    return 0;
}
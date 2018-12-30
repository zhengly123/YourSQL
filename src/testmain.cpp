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
    StdoutPrinter printer;
    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager rmManager(fm, bpm);
    IX_Manager ixManager(*fm, *bpm);
    SM_Manager smManager(ixManager, rmManager);
    QL_Manager qlManager(smManager, ixManager, rmManager, &printer);

    // std::cerr << "Before Test." << std::endl;

    int cnt = 0;

    /*
    for(;;)
    {
        printf("------ Inst Test #%d ------\n", ++cnt);
        if(treeparser(smManager, qlManager, 0)){
            printf("------ Inst Test End ------\n");
            break;
        }
    }
     */

    // freopen("./insert_test/ins_typemismatch.txt","r",stdin);
    freopen("../src/gtestcase/QL_SELECT3.in","r",stdin);

    for(;;)
    {
        int rc = treeparser(smManager, qlManager, 0);
        switch(rc)
        {
            case PARSEREXIT : cerr << "> Exit." << endl; break;
            case QL_RELNOTEXIST : cerr << "> Rel not exist." << endl; break;
            case QL_INVALIDSIZE : cerr << "> Invalid size." << endl; break;
            case QL_TYPEUNMATCHED : cerr << "> Type mismatched." << endl; break;
            case QL_ATTRNOTNULL : cerr << "> Attr should not be null." << endl; break;
            case QL_STRTOOLONG : cerr << "> String too long." << endl; break;
            case QL_DUPLICATE : cerr << "> Insert Duplicated." << endl; break;
            case 0 : cerr << "> Normal." << endl;  break;
            default: cerr << "> Unrecognized Error." << endl; break;
        }
        if(rc == PARSEREXIT) break;
    }

    return 0;
}
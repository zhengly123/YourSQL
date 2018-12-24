//
// Created by 杨乐 on 2018/11/5.
//

#include "PF_Test/pftest.h"
#include "RM_Test/rmtest.h"
#include "IX_Test/ixtest.h"
#include "Parser/parser.h"
//#include "Parser/yacc.tab.cpp"

int main(int argc, char *argv[])
{

    //pf_test();
//    rm_test_basic1();
    //rm_test_error(argc, argv);
    rm_test_massive1();
    // ix_test();

//    yyparse();
//
//    AST *topl;
//    topl = &toplevel;
//
//    cerr << "Size = " << topl->stmt_list.size() << endl;

    return 0;
}
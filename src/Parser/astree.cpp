//
// Created by 杨乐 on 2018/12/10.
//

#include "astree.h"
#include "yacc.tab.cpp"

void treeparser(SM_Manager &smm)
{
    yyparse();

    AST *topl;
    topl = &toplevel;

    std::cerr << "Size = " << topl->stmt_list.size() << std::endl;

    for(std::list<istmt>::iterator it = topl->stmt_list.begin(); it != topl->stmt_list.end(); ++ it)
        stmtparser(smm, *it);
}

void stmtparser(SM_Manager &smm, istmt st)
{
    switch (st.stmt_type)
    {
        case SHOW_DB :
            //smm.
            break;
        case CREATE_DB :
            smm.OpenDb(st.db_name.c_str());
            break;
        case DROP_DB :
            smm.CloseDb();
            break;
        case USE_DB :
            break;
        case SHOW_TABLE :
            break;
        default :
            break;
    }
}
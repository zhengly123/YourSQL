//
// Created by 杨乐 on 2018/12/10.
//

#include "astree.h"
#include "yacc.tab.cpp"

void tester(int ident, std::string str)
{
    for(int i = 0; i < ident; ++ i)
        std::cerr << " ";
    std::cerr << str << std::endl;
}

void treeparser(SM_Manager &smm)
{
    yyparse();

    ASType *topl;
    topl = &toplevel;

    // field list check
    // fieldlistparser(topl->field_list);

    // value list check
    // valuelistsparser(topl->value_lists);

    // set clause list check
    // setclauselistparser(topl->setcl_list);

    // selector check
    // selectorparser(topl->sel);

    // where clause check
    // wherelistparser(topl->where_list);


    for(std::list<istmt>::iterator it = topl->stmt_list.begin(); it != topl->stmt_list.end(); ++ it)
        stmtparser(smm, *it);
}

void stmtparser(SM_Manager &smm, istmt st)
{
    switch (st.id)
    {
        case SHOW_DB :
            std::cerr << "[Stmt] show databases" << std::endl;
            break;
        case CREATE_DB :
            //smm.OpenDb(st.dbName.c_str());
            std::cerr << "[Stmt] open database" << std::endl;
            std::cerr << "       [dbName]" << st.dbName << std::endl;
            break;
        case DROP_DB :
            //smm.CloseDb();
            std::cerr << "[Stmt] drop database" << std::endl;
            std::cerr << "       [dbName]" << st.dbName << std::endl;
            break;
        case USE_DB :
            std::cerr << "[Stmt] use database" << std::endl;
            std::cerr << "       [dbName]" << st.dbName << std::endl;
            break;
        case SHOW_TABLE :
            std::cerr << "[Stmt] show tables" << std::endl;
            break;
        case CREATE_TABLE :
            std::cerr << "[Stmt] create table" << std::endl;
            std::cerr << "       [tbName]" << st.tbName << std::endl;
            std::cerr << "       [fieldList] " << std::endl;
            fieldlistparser(st.field_list);
            break;
        case DROP_TABLE :
            std::cerr << "[Stmt] drop table" << std::endl;
            std::cerr << "       [tbName]" << st.tbName << std::endl;
            break;
        case DESC_ST :
            std::cerr << "[Stmt] desc" << std::endl;
            std::cerr << "       [tbName]" << st.tbName << std::endl;
            break;
        case INSERT_ST :
            std::cerr << "[Stmt] insertion" << std::endl;
            std::cerr << "       [tbName]" << st.tbName << std::endl;
            std::cerr << "       [valueLists] " << std::endl;
            valuelistsparser(st.value_lists);
            break;
        case DELETE_ST :
            std::cerr << "[Stmt] deletion" << std::endl;
            std::cerr << "       [tbName]" << st.tbName << std::endl;
            std::cerr << "       [whereClause] " << std::endl;
            wherelistparser(st.where_list);
            break;
        case UPDATE_ST :
            std::cerr << "[Stmt] update" << std::endl;
            std::cerr << "       [tbName]" << st.tbName << std::endl;
            std::cerr << "       [setClause] " << std::endl;
            setclauselistparser(st.setcl_list);
            std::cerr << "       [whereClause] " << std::endl;
            wherelistparser(st.where_list);
            break;
        case SELECT_ST :
            std::cerr << "[Stmt] select" << std::endl;
            std::cerr << "       [selector] ";
            selectorparser(st.sel);
            std::cerr << std::endl;
            std::cerr << "       [tableList] ";
            tableparser(st.table_list);
            std::cerr << std::endl;
            std::cerr << "       [whereClause] " << std::endl;
            wherelistparser(st.where_list);
            break;
        case CREATE_IDX :
            std::cerr << "[Stmt] create index" << std::endl;
            std::cerr << "       [tbName]" << st.tbName << std::endl;
            std::cerr << "       [colName]" << st.colName << std::endl;
            break;
        case DROP_IDX :
            std::cerr << "[Stmt] drop index" << std::endl;
            std::cerr << "       [tbName]" << st.tbName << std::endl;
            std::cerr << "       [colName]" << st.colName << std::endl;
            break;
        default :
            break;
    }
}

std::string typeparser(itype ty)
{
    switch (ty.id)
    {
        case INT_TYPE : return "int";
        case INT_CONST_TYPE : return "int (" + std::to_string(ty.value_int) + ")";
        case VARCHAR_TYPE : return "varchar";
        case VARCHAR_CONST_TYPE : return "varchar (" + std::to_string(ty.value_int) + ")";
        case DATE_TYPE : return "date";
        case FLOAT_TYPE : return "float";
        default: return "error";
    }
}

void fieldlistparser(std::list<ifield> fdlist)
{
    int cnt = 0;
    for(std::list<ifield>::iterator fd = fdlist.begin(); fd != fdlist.end(); fd ++)
    {
        std::cerr << "             [subfield] " << ++cnt << std::endl;
        fieldparser(*fd);
    }
}

void fieldparser(ifield fd)
{
    switch (fd.id)
    {
        case COL_FIELD :
            std::cerr << "               [colName] " << fd.colName << " " << std::endl;
            std::cerr << "               [type] " << typeparser(fd.type) << std::endl;
            break;
        case NOTNULL_COL_FIELD :
            std::cerr << "               [colName] " << fd.colName << " NOT NULL" << std::endl;
            std::cerr << "               [type] " << typeparser(fd.type) << std::endl;
            break;
        case PRIMARY_FIELD :
            std::cerr << "               [coList] ";
            tableparser(fd.colList);
            std::cerr << "AS PRIMARY KEY" << std::endl;
            break;
        case FOREIGN_FIELD :
            std::cerr << "               [colName] " << fd.colName << ", AS FOREIGN KEY" << std::endl;
            std::cerr << "               [tbName] " << fd.tbName << " " << std::endl;
            std::cerr << "               [refColName] " << fd.refcolName << " " << std::endl;
            break;
        default:
            std::cerr << "               [Error] " <<  std::endl;
            break;
    }
}

void valuelistsparser(std::list<std::list<ivalue>> valuelists)
{
    //std::cerr << "Valuelists[" << valuelists.size() << "]" << std::endl;
    int cnt = 0;
    for(std::list<std::list<ivalue>>::iterator it = valuelists.begin(); it != valuelists.end(); ++ it)
    {
        std::cerr << "             [sublist] ";
        valuelistparser(*it);
        std::cerr << std::endl;
    }

}

void valuelistparser(std::list<ivalue> valuelist)
{
    //std::cerr << "    Valuelist[" << valuelist.size() << "]" << std::endl;
    for(std::list<ivalue>::iterator it = valuelist.begin(); it != valuelist.end(); ++ it)
    {
        valueparser(*it);
        std::cerr << ", ";
    }
}

void valueparser(ivalue value)
{
    switch(value.id)
    {
        case VALUE_INT_ID :
            std::cerr << "(INT) " << value.value_int;
            break;
        case VALUE_STRING_ID :
            std::cerr << "(STRING) " << value.value_string;
            break;
        case VALUE_NULL_ID :
            std::cerr << "(NULL)";
            break;
        default :
            std::cerr << "(Unrecognized Value)";
    }
}

void setclauseparser(isetcl sc)
{
    std::cerr << "               [colName] " << sc.colName << std::endl;
    std::cerr << "               [value] ";
    valueparser(sc.value);
    std::cerr << std::endl;
}

void setclauselistparser(std::list<isetcl> sclist)
{
    int cnt = 0;
    for(std::list<isetcl>::iterator it = sclist.begin(); it != sclist.end(); ++ it)
    {
        std::cerr << "             [subclause] " << ++cnt << std::endl;
        setclauseparser(*it);
    }

}

void colparser(icol cl)
{
    if(cl.flag == 0)
    {
        std::cerr << "([colName] " << cl.colName << ")";
    } else {
        std::cerr << "([tbName] " << cl.tbName << ", [colName] " << cl.colName << ")";
    }
}

void selectorparser(isel sl)
{
    if(sl.col_list.size() == 0)
    {
        std::cerr << "*";
    } else {
        for(std::list<icol>::iterator it = sl.col_list.begin(); it != sl.col_list.end(); ++ it)
            { colparser(*it); std::cerr << ", "; }
    }
}

void opparser(int op)
{
    //std::cerr << "OP ";
    switch (op)
    {
        case EQ_OPER:
            std::cerr << "=";
            break;
        case NEQ_OPER:
            std::cerr << "<>";
            break;
        case LEQ_OPER :
            std::cerr << "<=";
            break;
        case GEQ_OPER :
            std::cerr << ">=";
            break;
        case LT_OPER :
            std::cerr << "<";
            break;
        case GT_OPER:
            std::cerr << ">";
            break;
        default:
            std::cerr << "Error";
    }
}

void whereparser(iwhere wh)
{
    //std::cerr << "Where Clause : " << std::endl;
    switch(wh.id)
    {
        case COL_V_WHERECLAUSE :
            std::cerr << "               [col] ";
            colparser(wh.fi);
            std::cerr << std::endl;

            std::cerr << "               [op] ";
            opparser(wh.oper);
            std::cerr << std::endl;

            std::cerr << "               [value] ";
            valueparser(wh.sval);
            std::cerr << std::endl;
            break;

        case COL_C_WHERECLAUSE :

            std::cerr << "               [col_1] ";
            colparser(wh.fi);
            std::cerr << std::endl;

            std::cerr << "               [op] ";
            opparser(wh.oper);
            std::cerr << std::endl;

            std::cerr << "               [col_2] ";
            colparser(wh.scol);
            std::cerr << std::endl;
            break;

        case COL_ISNULL_WHERECLAUSE :

            std::cerr << "               [col] ";
            colparser(wh.fi);
            std::cerr << std::endl;

            std::cerr << "               [op] IS NULL" << std::endl;
            break;

        case COL_ISNOTNULL_WHERECLAUSE :

            std::cerr << "               [col] ";
            colparser(wh.fi);
            std::cerr << std::endl;

            std::cerr << "               [op] IS NOT NULL" << std::endl;
            break;

        default:
            //std::cerr << "Where Clause Error." << std::endl;
            std::cerr << "               [Error] " << std::endl;
            break;
    }
}

void wherelistparser(std::list<iwhere> whlist)
{
    //std::cerr << "Where Clause List: " << std::endl;
    int cnt = 0;
    for(std::list<iwhere>::iterator it = whlist.begin(); it != whlist.end(); ++ it)
    {
        std::cerr << "             [subclause] " << ++cnt << std::endl;
        whereparser(*it);
    }

}

void tableparser(std::list<std::string> table)
{
    for(std::list<std::string>::iterator it = table.begin(); it != table.end(); ++ it)
        std::cerr << *it << ", ";
}

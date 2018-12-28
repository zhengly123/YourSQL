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

// flush = 0, single inst (test mode)
// flush = 1, multiple inst
// flush = 2, multiple inst (terminal mode)

int treeparser(SM_Manager &smm, QL_Manager &qlm, int flush)
{
    ASType *topl;
    exitFlag = 0;

    do
    {
        if(flush == 2) std :: cerr << ">$ ";

        parserError = 0;

        yyparse();

        if(parserError)
        {
            std::cerr << "Syntax Error." << std::endl;
            continue;
        }

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
        // wherelistparser(topl->where_list)

        // std::cerr << "Before Parse ... " << endl;

        for(std::list<istmt>::iterator it = topl->stmt_list.begin(); it != topl->stmt_list.end(); ++ it)
        {
            int rc = stmtparser(smm, qlm, *it);
            if(rc) return rc;
        }

        if(exitFlag) return PARSEREXIT;

    }while(flush);

    return 0;

}

int stmtparser(SM_Manager &smm, QL_Manager &qlm, istmt st)
{
    int len, cnt, lens, lenw, lensc, lenwr;
    AttrInfo * atrv;
    Value * vali;
    int lend;
    Condition * condi, * conds, *condw, *condwr;
    RelAttr *selist;
    int rc;

    switch (st.id) {

        case SHOW_DB :
            //std::cerr << "[Stmt] show databases" << std::endl;
            // TODO: smm.showDatabases();
//            smm.PrintTables();
            break;

        case CREATE_DB :
            //std::cerr << "[Stmt] open database" << std::endl;
            //std::cerr << "       [dbName]" << st.dbName << std::endl;
            smm.CreateDb(st.dbName.c_str());
            break;

        case DROP_DB :
            //std::cerr << "[Stmt] drop database" << std::endl;
            //std::cerr << "       [dbName]" << st.dbName << std::endl;
            smm.DestroyDb(st.dbName.c_str());
            break;

        case USE_DB :
            //std::cerr << "[Stmt] use database" << std::endl;
            //std::cerr << "       [dbName]" << st.dbName << std::endl;
            if (st.dbName != currentDB)
            {
                if (!currentDB.empty())
                    smm.CloseDb(); // close current db
                currentDB = st.dbName;
                smm.OpenDb(currentDB.c_str());
            }
            break;

        case SHOW_TABLE :
            smm.PrintTables();
            //std::cerr << "[Stmt] show tables" << std::endl;
            break;

        case CREATE_TABLE :
            //std::cerr << "[Stmt] create table" << std::endl;
            //std::cerr << "       [tbName]" << st.tbName << std::endl;
            //std::cerr << "       [fieldList] " << std::endl;

            // std::cerr << "Create Table ... " << std::endl;

            len = st.field_list.size();
            cnt = 0;

            atrv = new AttrInfo[len];
            fieldlistparser(st.field_list, atrv, cnt);
            smm.CreateTable(st.tbName.c_str(), cnt, atrv);
            delete[] atrv;

            break;

        case DROP_TABLE :
            //std::cerr << "[Stmt] drop table" << std::endl;
            //std::cerr << "       [tbName]" << st.tbName << std::endl;

            smm.DropTable(st.tbName.c_str());
            break;

        case DESC_ST :
            //std::cerr << "[Stmt] desc" << std::endl;
            //std::cerr << "       [tbName]" << st.tbName << std::endl;

            // TODO: smm.Desc();
            break;

        case INSERT_ST :
            //std::cerr << "[Stmt] insertion" << std::endl;
            //std::cerr << "       [tbName]" << st.tbName << std::endl;
            //std::cerr << "       [valueLists] " << std::endl;
            //valuelistsparser(st.value_lists);

            for(std::list<std::list<ivalue>>::iterator it = st.value_lists.begin(); it != st.value_lists.end(); ++ it)
            {
                len = (*it).size();
                vali = new Value[len];
                valuelistparser(*it, vali);
                int rc = qlm.Insert(st.tbName.c_str(), len, vali);
                delete[] vali;
                if(rc) return rc;
            }

            break;

        case DELETE_ST :
            //std::cerr << "[Stmt] deletion" << std::endl;
            //std::cerr << "       [tbName]" << st.tbName << std::endl;
            //std::cerr << "       [whereClause] " << std::endl;
            //wherelistparser(st.where_list);

            lend = st.where_list.size();
            condi = new Condition[lend];
            wherelistparser(st.where_list, condi);
            qlm.Delete(st.tbName.c_str(), lend, condi);
            delete[] condi;

            break;

        case UPDATE_ST :

            //std::cerr << "[Stmt] update" << std::endl;
            //std::cerr << "       [tbName]" << st.tbName << std::endl;
            //std::cerr << "       [setClause] " << std::endl;
            //setclauselistparser(st.setcl_list);
            //std::cerr << "       [whereClause] " << std::endl;
            //wherelistparser(st.where_list);

            lens = st.setcl_list.size();
            conds = new Condition[lens];
            setclauselistparser(st.setcl_list, conds);

            lenw = st.where_list.size();
            condw = new Condition[lenw];
            wherelistparser(st.where_list, condw);

            qlm.Update(st.tbName.c_str(), lens, conds, lenw, condw);

            delete[] conds;
            delete[] condw;

            break;

        case SELECT_ST :
            //std::cerr << "[Stmt] select" << std::endl;
            //std::cerr << "       [selector] ";
            //selectorparser(st.sel);
            //std::cerr << std::endl;
            //std::cerr << "       [tableList] ";
            //tableparser(st.table_list);
            //std::cerr << std::endl;
            //std::cerr << "       [whereClause] " << std::endl;
            //wherelistparser(st.where_list);

            lensc = st.sel.col_list.size();
            selist = new RelAttr[lensc];
            selectorparser(st.sel, selist);

            lenwr = st.where_list.size();
            condwr = new Condition[lenwr];
            wherelistparser(st.where_list, condwr);

            qlm.Select(lensc, selist, st.table_list, lenwr, condwr);

            delete[] selist;
            delete[] condw;

            break;

        case CREATE_IDX :
            //std::cerr << "[Stmt] create index" << std::endl;
            //std::cerr << "       [tbName]" << st.tbName << std::endl;
            //std::cerr << "       [colName]" << st.colName << std::endl;

            smm.CreateIndex(st.tbName.c_str(), st.colName.c_str());
            break;

        case DROP_IDX :
            //std::cerr << "[Stmt] drop index" << std::endl;
            //std::cerr << "       [tbName]" << st.tbName << std::endl;
            //std::cerr << "       [colName]" << st.colName << std::endl;

            smm.DropIndex(st.tbName.c_str(), st.colName.c_str());
            break;

        case EXIT_ST :

            exitFlag = 1;
            break;

        case CLOSE_ST :

            smm.CloseDb();
            currentDB = "";
            break;

        case SHOW_TABLE_ID :

            rc = qlm.showRelation(st.tbName.c_str());
            if(rc) return rc;
            break;

        default :
            break;
    }

    return 0;
}

AttrType typeparser(itype ty)
{
    switch (ty.id)
    {
        case INT_TYPE : return INT;
        //case INT_CONST_TYPE : return "int (" + std::to_string(ty.value_int) + ")";
        case VARCHAR_TYPE : return STRING;
        //case VARCHAR_CONST_TYPE : return "varchar (" + std::to_string(ty.value_int) + ")";
        //case DATE_TYPE : return "date";
        case FLOAT_TYPE : return FLOAT;
        default: return ERRTYPE;
    }
}

void fieldlistparser(std::list<ifield> fdlist, struct AttrInfo * atrv, int &cnt)
{
    cnt = 0;

    std::list<std::string> primarylist;

    for(std::list<ifield>::iterator fd = fdlist.begin(); fd != fdlist.end(); fd ++)
    {
        //std::cerr << "             [subfield] " << std::endl;

        if(fd->id == PRIMARY_FIELD)
        {
            // Not a real field but primary key
            primarylist.insert(primarylist.begin(), fd->colList.begin(), fd->colList.end());
            continue;
        }
        else
        {
            fieldparser(*fd, atrv + cnt);
            ++ cnt;
        }
    }

    for(std::list<std::string>::iterator coli = primarylist.begin(); coli != primarylist.end(); coli ++)
    {
        std::string coln = *coli;
        int found = 0;

        for(int i = 0; i < cnt; ++ i)
            if(strcmp(coln.c_str(), atrv[i].attrName) == 0)
                atrv[i].flag |= 2, found = 1;

        if(!found)
        {
            // TODO: Error Handle!
        }
    }

}

int typelength(AttrType ty)
{
    switch (ty)
    {
        case INT: return 4;
        case FLOAT: return 4;
        case STRING: return MAXNAME+1;
        default: return 4;
    }
}

void fieldparser(ifield fd, struct AttrInfo * atrv)
{
    switch (fd.id)
    {
        case COL_FIELD :
            //std::cerr << "               [colName] " << fd.colName << " " << std::endl;
            //std::cerr << "               [type] " << typeparser(fd.type) << std::endl;

            strcpy(atrv->attrName, fd.colName.c_str());
            atrv->flag = 0;
            atrv->attrType = typeparser(fd.type);
            atrv->attrLength = typelength(atrv->attrType);
            break;

            case NOTNULL_COL_FIELD :
            //std::cerr << "               [colName] " << fd.colName << " NOT NULL" << std::endl;
            //std::cerr << "               [type] " << typeparser(fd.type) << std::endl;

            strcpy(atrv->attrName, fd.colName.c_str());
            atrv->flag = 1;
            atrv->attrType = typeparser(fd.type);
            atrv->attrLength = typelength(atrv->attrType);
            break;

        case PRIMARY_FIELD :
            //std::cerr << "               [coList] ";
            tableparser(fd.colList);
            //std::cerr << "AS PRIMARY KEY" << std::endl;
            break;

        case FOREIGN_FIELD :
            //std::cerr << "               [colName] " << fd.colName << ", AS FOREIGN KEY" << std::endl;
            //std::cerr << "               [tbName] " << fd.tbName << " " << std::endl;
            //std::cerr << "               [refColName] " << fd.refcolName << " " << std::endl;
            break;
        default:
            std::cerr << "               [Error] " <<  std::endl;
            break;
    }
}

void valuelistparser(std::list<ivalue> valuelist, Value * val)
{
    //std::cerr << "    Valuelist[" << valuelist.size() << "]" << std::endl;
    int cnt = 0;
    for(std::list<ivalue>::iterator it = valuelist.begin(); it != valuelist.end(); ++ it)
    {
        valueparser(*it, val + cnt);
        ++ cnt;
    }
}

void valueparser(ivalue value, Value * val)
{
    switch(value.id)
    {
        case VALUE_INT_ID :
            val->type = INT;
            val->data = new int (value.value_int);
            break;

        case VALUE_STRING_ID :
            val->type = STRING;
            val->data = new char[value.value_string.length()+1];
            strcpy((char*) val->data, value.value_string.c_str());
            break;

        case VALUE_NULL_ID :
            val->type = NULLTYPE;
            break;

        default :
            std::cerr << "(Unrecognized Value)";
    }
}

void setclauseparser(isetcl sc, struct Condition * con)
{
    //colparser(sc.colName, &con->lhsAttr);
    con->lhsAttr.relName = nullptr;
    strcpy(con->lhsAttr.attrName, sc.colName.c_str());

    //con->op = opparser(wh.oper);
    //con->flag = 0;
    con->bRhsIsAttr = false;
    valueparser(sc.value, &con->rhsValue);

    //std::cerr << "               [colName] " << sc.colName << std::endl;
    //std::cerr << "               [value] ";
    //valueparser(sc.value);
    //std::cerr << std::endl;
}

void setclauselistparser(std::list<isetcl> sclist, struct Condition * con)
{
    int cnt = 0;
    for(std::list<isetcl>::iterator it = sclist.begin(); it != sclist.end(); ++ it)
    {
        //std::cerr << "             [subclause] " << ++cnt << std::endl;
        setclauseparser(*it, con + cnt);
        ++ cnt;
    }

}

void colparser(icol cl, struct RelAttr * rel)
{
    if(cl.flag == 0)
    {
        rel->relName = nullptr;
        strcpy(rel->attrName, cl.colName.c_str());
    } else {
        strcpy(rel->relName, cl.tbName.c_str()); 
        strcpy(rel->attrName, cl.colName.c_str());
    }
}

void selectorparser(isel sl, struct RelAttr * rel)
{
    if(sl.col_list.size() == 0)
    {
        //std::cerr << "*";
    } else {
        int cnt = 0;
        for(std::list<icol>::iterator it = sl.col_list.begin(); it != sl.col_list.end(); ++ it)
        {
            colparser(*it, rel + cnt); 
            ++ cnt;
        }
    }
}

CompOp opparser(int op)
{
    //std::cerr << "OP ";
    switch (op)
    {
        case EQ_OPER : return EQ_OP;
        case NEQ_OPER: return NE_OP;
        case LEQ_OPER: return LE_OP;
        case GEQ_OPER: return GE_OP;
        case LT_OPER : return LT_OP;
        case GT_OPER : return GT_OP;
        default:       return NO_OP;
    }
}

void whereparser(iwhere wh, struct Condition * con)
{
    //std::cerr << "Where Clause : " << std::endl;
    switch(wh.id)
    {
        case COL_V_WHERECLAUSE :
            
            colparser(wh.fi, &con->lhsAttr);
            con->op = opparser(wh.oper);
            con->flag = 0;
            con->bRhsIsAttr = false;
            valueparser(wh.sval, &con->rhsValue);
            break;

        case COL_C_WHERECLAUSE :

            colparser(wh.fi, &con->lhsAttr);
            con->op = opparser(wh.oper);
            con->flag = 0;
            con->bRhsIsAttr = false;
            colparser(wh.scol, &con->rhsAttr);
            break;

        case COL_ISNULL_WHERECLAUSE :

            colparser(wh.fi, &con->lhsAttr);
            con->flag = 1;
            break;

        case COL_ISNOTNULL_WHERECLAUSE :

            colparser(wh.fi, &con->lhsAttr);
            con->flag = 2;
            break;

        default:
            //std::cerr << "Where Clause Error." << std::endl;
            //std::cerr << "               [Error] " << std::endl;
            break;
    }
}

void wherelistparser(std::list<iwhere> whlist, struct Condition * con)
{
    //std::cerr << "Where Clause List: " << std::endl;
    int cnt = 0;
    for(std::list<iwhere>::iterator it = whlist.begin(); it != whlist.end(); ++ it)
    {
        //std::cerr << "             [subclause] " << ++cnt << std::endl;
        whereparser(*it, con + cnt);
        ++ cnt;
    }

}

void tableparser(std::list<std::string> table)
{
    for(std::list<std::string>::iterator it = table.begin(); it != table.end(); ++ it)
        std::cerr << *it << ", ";
}

void clearParser()
{
    currentDB = "";
}

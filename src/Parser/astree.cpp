//
// Created by 杨乐 on 2018/12/10.
//

#include <cstring>
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
    int len, cnt, lens, lenw, lensc, lenwr, leno, leng;
    AttrInfo * atrv;
    Value * vali;
    int lend;
    Condition * condi, * conds, *condw, *condwr;
    RelAttr *selist, *ordlist, *grplist;
    int rc;

    switch (st.id) {

        case SHOW_DB :
            //std::cerr << "[Stmt] show databases" << std::endl;
            // TODO: smm.showDatabases();
//            smm.PrintTables();
            break;

        case CREATE_DB :

            smm.CreateDb(st.dbName.c_str());
            break;

        case DROP_DB :

            smm.DestroyDb(st.dbName.c_str());
            break;

        case USE_DB :

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

            len = st.field_list.size();
            cnt = 0;

            atrv = new AttrInfo[len];
            memset(atrv, 0, sizeof(AttrInfo) * len);
            fieldlistparser(st.field_list, atrv, cnt);
            smm.CreateTable(st.tbName.c_str(), cnt, atrv);
            delete[] atrv;

            break;

        case DROP_TABLE :

            smm.DropTable(st.tbName.c_str());
            break;

        case DESC_ST :

            // TODO: smm.Desc();
            break;

        case INSERT_ST :

            for(std::list<std::list<ivalue>>::iterator it = st.value_lists.begin(); it != st.value_lists.end(); ++ it)
            {
                len = (*it).size();
                vali = new Value[len];
                memset(vali, 0, sizeof(Value) * len);
                if(rc = valuelistparser(*it, vali)) return rc;
                rc = qlm.Insert(st.tbName.c_str(), len, vali);
                delete[] vali;
                if(rc) return rc;
            }

            break;

        case DELETE_ST :

            lend = st.where_list.size();
            condi = new Condition[lend];
            memset(condi, 0, sizeof(Condition) * lend);
            wherelistparser(st.where_list, condi);
            qlm.Delete(st.tbName.c_str(), lend, condi);
            delete[] condi;

            break;

        case UPDATE_ST :

            lens = st.setcl_list.size();
            conds = new Condition[lens];
            memset(conds, 0, sizeof(Condition) * lens);
            setclauselistparser(st.setcl_list, conds);

            lenw = st.where_list.size();
            condw = new Condition[lenw];
            memset(condw, 0, sizeof(Condition) * lenw);
            wherelistparser(st.where_list, condw);

            qlm.Update(st.tbName.c_str(), lens, conds, lenw, condw);

            delete[] conds;
            delete[] condw;

            break;

        case SELECT_ST :

            lensc = st.sel.col_list.size();
            selist = new RelAttr[lensc];
            memset(selist, 0, sizeof(RelAttr) * lensc);
            selectorparser(st.sel, selist);

            lenwr = st.where_list.size();
            condwr = new Condition[lenwr];
            memset(condwr, 0, sizeof(Condition) * lenwr);
            wherelistparser(st.where_list, condwr);

            leng = st.group_list.size();
            grplist = new RelAttr[leng];
            grouplistparser(st.group_list, grplist);

            leno = st.order_list.size();
            ordlist = new RelAttr[leno];
            orderlistparser(st.order_list, ordlist);

            if(rc = qlm.Select(lensc, selist, st.table_list, lenwr, condwr, leng, grplist, leno, ordlist))
                return rc;

            delete[] selist;
            delete[] ordlist;
            delete[] condwr;

            break;

        case CREATE_IDX :

            smm.CreateIndex(st.tbName.c_str(), st.colName.c_str());
            break;

        case DROP_IDX :

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
        case DATE_TYPE : return DATETYPE;
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

int valuelistparser(std::list<ivalue> valuelist, Value * val)
{
    //std::cerr << "    Valuelist[" << valuelist.size() << "]" << std::endl;
    int cnt = 0, rc;
    for(std::list<ivalue>::iterator it = valuelist.begin(); it != valuelist.end(); ++ it)
    {
        if(rc = valueparser(*it, val + cnt)) return rc;
        ++ cnt;
    }
    return 0;
}

int valueparser(ivalue value, Value * val)
{
    std::string s;
    int dt;

    switch(value.id)
    {
        case VALUE_INT_ID :
            val->type = INT;
            val->data = new int (value.value_int);
            break;

        case VALUE_STRING_ID :
            val->type = STRING;
            if(value.value_string.length() > MAXNAME) return QL_STRTOOLONG;
            val->data = new char[MAXNAME+1];
            memset(val->data, 0, MAXNAME+1);
            strcpy((char*) val->data, value.value_string.c_str());
            break;

        case VALUE_FLOAT_ID :
            val->type = FLOAT;
            val->data = new float (value.value_float);
            break;

        case VALUE_DATE_ID :
            val->type = DATETYPE;
            s = value.value_string;
            dt = atoi(s.substr(0,3).c_str()) * 10000 + atoi(s.substr(5,6).c_str()) * 100 + atoi(s.substr(8,9).c_str());
            val->data = new int (dt);
            break;

        case VALUE_NULL_ID :
            val->type = NULLTYPE;
            break;

        default :
            std::cerr << "(Unrecognized Value)";
    }

    return 0;
}

void setclauseparser(isetcl sc, struct Condition * con)
{
    con->lhsAttr.relName = NULL;
    con->lhsAttr.attrName = new char[sc.colName.size() + 1];
    strcpy(con->lhsAttr.attrName, sc.colName.c_str());
    con->bRhsIsAttr = false;
    valueparser(sc.value, &con->rhsValue);
}

void setclauselistparser(std::list<isetcl> sclist, struct Condition * con)
{
    int cnt = 0;
    for(std::list<isetcl>::iterator it = sclist.begin(); it != sclist.end(); ++ it)
    {
        setclauseparser(*it, con + cnt);
        ++ cnt;
    }

}

void colparser(icol cl, struct RelAttr * rel)
{
    if(cl.flag == 0)
    {
        rel->relName = NULL;
        rel->attrName = new char[cl.colName.size() + 1];
        strcpy(rel->attrName, cl.colName.c_str());
    } else {
        rel->relName = new char[cl.tbName.size() + 1];
        strcpy(rel->relName, cl.tbName.c_str());
        rel->attrName = new char[cl.colName.size() + 1];
        strcpy(rel->attrName, cl.colName.c_str());
    }

    switch(cl.aggtype)
    {
        case AGG_MAX : rel->op = AGGREGATE_MAX; break;
        case AGG_MIN : rel->op = AGGREGATE_MIN; break;
        case AGG_AVG : rel->op = AGGREGATE_AVG; break;
        case AGG_SUM : rel->op = AGGREGATE_SUM; break;
        default: rel->op = 0; break;
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

void orderparser(icol cl, RelAttr * rel)
{
    if(cl.flag == 0)
    {
        rel->relName = NULL;
        rel->attrName = new char[cl.colName.size() + 1];
        strcpy(rel->attrName, cl.colName.c_str());
    } else {
        rel->relName = new char[cl.tbName.size() + 1];
        strcpy(rel->relName, cl.tbName.c_str());
        rel->attrName = new char[cl.colName.size() + 1];
        strcpy(rel->attrName, cl.colName.c_str());
    }

    switch(cl.aggtype)
    {
        case AGG_MAX : rel->op = AGGREGATE_MAX; break;
        case AGG_MIN : rel->op = AGGREGATE_MIN; break;
        case AGG_AVG : rel->op = AGGREGATE_AVG; break;
        case AGG_SUM : rel->op = AGGREGATE_SUM; break;
        default: rel->op = 0; break;
    }

    switch(cl.ordtype)
    {
        case ORDER_BY_INC : rel->ord = ORD_INC; break;
        case ORDER_BY_DEC : rel->ord = ORD_DEC; break;
        default: rel->ord = 0; break;
    }
}

void orderlistparser(std::list<icol> ordlist, struct RelAttr * rel)
{
    int cnt = 0;
    for(std::list<icol>::iterator it = ordlist.begin(); it != ordlist.end(); ++ it)
    {
        orderparser(*it, rel + cnt);
        ++ cnt;
    }
}

void grouplistparser(std::list<icol> grplist, struct RelAttr * rel)
{
    int cnt = 0;
    for(std::list<icol>::iterator it = grplist.begin(); it != grplist.end(); ++ it)
    {
        colparser(*it, rel + cnt);
        ++ cnt;
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
            con->flag = COND_NORMAL;
            con->bRhsIsAttr = false;
            valueparser(wh.sval, &con->rhsValue);
            break;

        case COL_C_WHERECLAUSE :

            colparser(wh.fi, &con->lhsAttr);
            con->op = opparser(wh.oper);
            con->flag = COND_NORMAL;
            con->bRhsIsAttr = true;
            colparser(wh.scol, &con->rhsAttr);
            break;

        case COL_ISNULL_WHERECLAUSE :

            colparser(wh.fi, &con->lhsAttr);
            con->flag = COND_ISNULL;
            break;

        case COL_ISNOTNULL_WHERECLAUSE :

            colparser(wh.fi, &con->lhsAttr);
            con->flag = COND_NOTNULL;
            break;

        case COL_LIKECLAUSE :

            colparser(wh.fi, &con->lhsAttr);
            con->flag = COND_LIKE;
            con->pattern = wh.pattern;
            break;

        case COL_NOTLIKECLAUSE :

            colparser(wh.fi, &con->lhsAttr);
            con->flag = COND_NOTLIKE;
            con->pattern = wh.pattern;
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

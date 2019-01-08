//
// Created by 杨乐 on 2018/12/10.
//

#include <cstring>
#include "astree.h"
#include "yacc.tab.cpp"
#include "parsererror.h"
#include "../Printer/CsvPrinter.h"

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
    int flag, rc;
    std::string relName;

    switch (st.id) {

        case SHOW_DB :

            break;

        case CREATE_DB :

            rc = smm.CreateDb(st.dbName.c_str());
            if(rc) return rc;
#ifdef TERMMSG
            printf("INFO : Create DB %s.\n", st.dbName.c_str());
#endif
            break;

        case DROP_DB :

            smm.DestroyDb(st.dbName.c_str());
            if(rc) return rc;
#ifdef TERMMSG
            printf("INFO : Drop DB %s.\n", st.dbName.c_str());
#endif

            break;

        case USE_DB :

            if (st.dbName != currentDB)
            {
                if (!currentDB.empty())
                    smm.CloseDb(); // close current db
                currentDB = st.dbName;
                rc = smm.OpenDb(currentDB.c_str());
                if(rc) return rc;
#ifdef TERMMSG
                printf("INFO : Use DB %s.\n", st.dbName.c_str());
#endif
            }
            else
            {
#ifdef TERMMSG
                printf("INFO : DB %s is already in use.\n", st.dbName.c_str());
#endif
            }
            break;

        case SHOW_TABLE :
            rc = smm.PrintTables();
            if (rc) return rc;
            //std::cerr << "[Stmt] show tables" << std::endl;
            break;

        case CREATE_TABLE :

            len = st.field_list.size();
            cnt = 0;

            atrv = new AttrInfo[len];
            memset(atrv, 0, sizeof(AttrInfo) * len);

            if(rc = fieldlistparser(st.field_list, atrv, cnt))
                {delete[] atrv; return rc;}

            if(rc = smm.CreateTable(st.tbName.c_str(), cnt, atrv))
                {delete[] atrv; return rc;}

            delete[] atrv;

#ifdef TERMMSG
            printf("INFO : Table %s created.\n", st.tbName.c_str());
#endif

            break;

        case DROP_TABLE :

            rc = smm.DropTable(st.tbName.c_str());
            if(rc) return rc;
#ifdef TERMMSG
            printf("INFO : Table %s dropped.\n", st.tbName.c_str());
#endif
            break;

        case DESC_ST :

            // TODO: smm.Desc();
            break;

        case INSERT_ST :

            flag = 0;
            for(std::list<std::list<ivalue>>::iterator it = st.value_lists.begin(); it != st.value_lists.end(); ++ it)
            {
                len = (*it).size();
                vali = new Value[len];
                memset(vali, 0, sizeof(Value) * len);
                rc = valuelistparser(*it, vali);
                //if(rc) return rc;
                if(rc == 0) rc = qlm.Insert(st.tbName.c_str(), len, vali);
                delete[] vali;
                if(rc == 0) ++ flag;
                else
                {
#ifdef TERMMSG
                    printf("ERROR: %s\n", errorGet(rc).c_str());
#endif
                }
                //if(rc) return rc;
            }

             if(rc) return rc;

#ifdef TERMMSG
            printf("INFO : Insert cnt = %d\n", flag);
#endif

            break;

        case DELETE_ST :

            lend = st.where_list.size();
            condi = new Condition[lend];
            memset(condi, 0, sizeof(Condition) * lend);
            wherelistparser(st.where_list, condi);

            relName = st.tbName;
            flag = 1;
            rc = 0;

            for(int i = 0; i < lend; ++ i)
            {
                if(rc = appendRel(condi[i].lhsAttr.relName, relName.c_str())) break;
                if(condi[i].bRhsIsAttr) if(rc = appendRel(condi[i].rhsAttr.relName, relName.c_str())) break;
            }
            if(rc) flag = 0;

            if(flag) rc = qlm.Delete(st.tbName.c_str(), lend, condi);

            delete[] condi;

            if(rc) return rc;

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

            relName = st.tbName;
            flag = 1;
            rc = 0;

            for(int i = 0; i < lens; ++ i)
            {
                if(rc = appendRel(conds[i].lhsAttr.relName, relName.c_str())) break;
                if(conds[i].bRhsIsAttr) if(rc = appendRel(conds[i].rhsAttr.relName, relName.c_str())) break;
            }
            if(rc) flag = 0;

            for(int i = 0; i < lenw; ++ i)
            {
                if(rc = appendRel(condw[i].lhsAttr.relName, relName.c_str())) break;
                if(condw[i].bRhsIsAttr) if(rc = appendRel(condw[i].rhsAttr.relName, relName.c_str())) break;
            }
            if(rc) flag = 0;

            if(flag) rc = qlm.Update(st.tbName.c_str(), lens, conds, lenw, condw);

            delete[] conds;
            delete[] condw;

            if(rc) return rc;

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

            flag = 1;
            rc = 0;

            if(st.table_list.size() == 1) // only have one table to select
            {
                relName = st.table_list.front();
                for(int i = 0; i < lensc; ++ i) if(rc = appendRel(selist[i].relName, relName.c_str())) break;
                if(rc) flag = 0;
                for(int i = 0; i < lenwr; ++ i)
                {
                    if(rc = appendRel(condwr[i].lhsAttr.relName, relName.c_str())) break;
                    if(condwr[i].bRhsIsAttr) if(rc = appendRel(condwr[i].rhsAttr.relName, relName.c_str())) break;
                }
                if(rc) flag = 0;
                for(int i = 0; i < leng; ++ i) if(rc = appendRel(grplist[i].relName, relName.c_str())) break;
                if(rc) flag = 0;
                for(int i = 0; i < leno; ++ i) if(rc = appendRel(ordlist[i].relName, relName.c_str())) break;
                if(rc) flag = 0;
            }

            if(st.fileout.if_csv)
                qlm.setPrinter(csvPrinter);
            else
                qlm.setPrinter(stdoutPrinter);

            if(flag) rc = qlm.Select(lensc, selist, st.table_list, lenwr, condwr, leng, grplist, leno, ordlist);

            delete[] selist;
            delete[] ordlist;
            delete[] condwr;

            if(rc) return rc;

            if(st.fileout.if_csv)
            {
                std::string outputName = st.fileout.fileName;
                outputName = outputName.substr(1,outputName.length()-2);
                qlm.getPrinter()->flush(outputName);
            }
            else
            {
#ifndef GTEST
#ifndef SERVER
                qlm.getPrinter()->flush();
#endif
#endif
            }

#ifdef TERMMSG
            printf("INFO : Select cnt = %d.\n", qlm.selectsize);
#endif


            break;

        case CREATE_IDX :

            rc = smm.CreateIndex(st.tbName.c_str(), st.colName.c_str());
            if(rc) return rc;
#ifdef TERMMSG
            printf("INFO : Index created.\n");
#endif

            break;

        case DROP_IDX :

            rc = smm.DropIndex(st.tbName.c_str(), st.colName.c_str());
            if(rc) return rc;
#ifdef TERMMSG
            printf("INFO : Index dropped.\n");
#endif
            break;

        case EXIT_ST :

            exitFlag = 1;
            break;

        case CLOSE_ST :

            rc = smm.CloseDb();
            if(rc) return rc;
#ifdef TERMMSG
            printf("INFO : Database %s closed.\n", currentDB.c_str());
#endif
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
        case VARCHAR_TYPE : return STRING;
        case DATE_TYPE : return DATETYPE;
        case FLOAT_TYPE : return FLOAT;
        default: return ERRTYPE;
    }
}

int fieldlistparser(std::list<ifield> fdlist, struct AttrInfo * atrv, int &cnt)
{
    cnt = 0;

    std::list<std::string> primarylist;

    int rc = 0;

    for(std::list<ifield>::iterator fd = fdlist.begin(); fd != fdlist.end(); fd ++)
    {
        if(fd->id == PRIMARY_FIELD)
        {
            // Not a real field but primary key
            primarylist.insert(primarylist.begin(), fd->colList.begin(), fd->colList.end());
            continue;
        }
        else if(fd->id != FOREIGN_FIELD)
        {
            if(rc = fieldparser(*fd, atrv + cnt)) return rc;
            ++ cnt;
        }
    }

    if(primarylist.size() > 1)
        return PASERR_MULTIPLE_PRIMARY;

    for(std::list<std::string>::iterator coli = primarylist.begin(); coli != primarylist.end(); coli ++)
    {
        std::string coln = *coli;
        int found = 0;

        if(coln.length() > MAXNAME) return PASERR_ATTR_TOOLONG;

        for(int i = 0; i < cnt; ++ i)
            if(strcmp(coln.c_str(), atrv[i].attrName) == 0)
                atrv[i].flag |= 2, found = 1;

        if(!found)
        {
            return PASERR_PRIMARY_NOTFOUND;
        }
    }

    for(std::list<ifield>::iterator fd = fdlist.begin(); fd != fdlist.end(); fd ++)
        if(fd->id == FOREIGN_FIELD)
        {
            int found = -1;

            std::string colname = fd->colName;
            std::string tbname = fd->tbName;
            std::string refcolname = fd->refcolName;

            if(colname.length() > MAXNAME) return PASERR_ATTR_TOOLONG;
            if(tbname.length() > MAXNAME) return PASERR_ATTR_TOOLONG;
            if(refcolname.length() > MAXNAME) return PASERR_ATTR_TOOLONG;

            for(int i = 0; i < cnt; ++ i)
                if(strcmp(colname.c_str(), atrv[i].attrName) == 0) found = i;

            if(found < 0) return PASERR_FOREIGN_NOTFOUND;

            if(atrv[found].isForeign) return PASERR_FOREIGN_MULTIPLE;

            atrv[found].isForeign = 1;
            strcpy(atrv[found].foreignTable, tbname.c_str());
            strcpy(atrv[found].foreignName, refcolname.c_str());
        }

    return 0;
}

int fieldparser(ifield fd, struct AttrInfo * atrv)
{
    switch (fd.id)
    {
        case COL_FIELD :

            if(fd.colName.length() > MAXNAME) return PASERR_ATTR_TOOLONG;

            strcpy(atrv->attrName, fd.colName.c_str());

            atrv->flag = 0;
            atrv->isForeign = 0;
            atrv->attrType = typeparser(fd.type);
            atrv->attrLength = fd.type.length;

            break;

        case NOTNULL_COL_FIELD :

            if(fd.colName.length() > MAXNAME) return PASERR_ATTR_TOOLONG;

            strcpy(atrv->attrName, fd.colName.c_str());

            atrv->flag = 1;
            atrv->isForeign = 0;

            atrv->attrType = typeparser(fd.type);
            atrv->attrLength = fd.type.length;
            break;

        default:
            assert(false);
            break;
    }

    return 0;
}

int valuelistparser(std::list<ivalue> valuelist, Value * val)
{
    int cnt = 0, rc;
    for(std::list<ivalue>::iterator it = valuelist.begin(); it != valuelist.end(); ++ it)
    {
        if(rc = valueparser(*it, val + cnt)) return rc;
        ++ cnt;
    }
    return 0;
}

const int DayofMonth[] = {0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int validdate(int y, int m, int d)
{
    if(y < 0 || y > 9999) return 0;
    if(m < 1 || m > 12) return 0;
    if(d < 1 || d > 31) return 0;
    if(m != 2) return d <= DayofMonth[m];
    int rn = ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
    return d <= 28 + rn;
}

int valueparser(ivalue value, Value * val)
{
    std::string s;
    int dt, year, month, day;

    switch(value.id)
    {
        case VALUE_INT_ID :
            val->type = INT;
            val->data = new int (value.value_int);
            break;

        case VALUE_STRING_ID :
            val->type = STRING;
            val->data = new char[value.value_string.length()+1];
            memset(val->data, 0, value.value_string.length()+1);
            strcpy((char*) val->data, value.value_string.c_str());
            break;

        case VALUE_FLOAT_ID :
            val->type = FLOAT;
            val->data = new float (value.value_float);
            break;

        case VALUE_DATE_ID :
            val->type = DATETYPE;
            s = value.value_string;
            year = atoi(s.substr(1,4).c_str());
            month = atoi(s.substr(6,7).c_str());
            day = atoi(s.substr(9,10).c_str());
            if(!validdate(year, month, day)) return PASERR_DATE_ERROR;
            dt = year * 10000 + month * 100 + day;
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
    switch (op)
    {
        case EQ_OPER : return CompOp::EQ_OP;
        case NEQ_OPER: return CompOp::NE_OP;
        case LEQ_OPER: return CompOp::LE_OP;
        case GEQ_OPER: return CompOp::GE_OP;
        case LT_OPER : return CompOp::LT_OP;
        case GT_OPER : return CompOp::GT_OP;
        default:       return CompOp::NO_OP;
    }
}

void whereparser(iwhere wh, struct Condition * con)
{
    int len;

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
            con->bRhsIsAttr = false;
            break;

        case COL_ISNOTNULL_WHERECLAUSE :

            colparser(wh.fi, &con->lhsAttr);
            con->flag = COND_NOTNULL;
            con->bRhsIsAttr = false;
            break;

        case COL_LIKECLAUSE :

            colparser(wh.fi, &con->lhsAttr);
            con->op = CompOp::LK_OP;
            con->bRhsIsAttr = false;
            con->flag = CondType::COND_NORMAL;
            con->rhsValue.type = AttrType::STRING;

            con->rhsValue.data = new char[wh.pattern.length()+1];
            strcpy((char*)con->rhsValue.data, wh.pattern.data());

            break;

        case COL_NOTLIKECLAUSE :

            colparser(wh.fi, &con->lhsAttr);
            con->op = CompOp::UKL_OP;
            con->bRhsIsAttr = false;
            con->flag = CondType::COND_NORMAL;
            con->rhsValue.type = AttrType::STRING;

            con->rhsValue.data = new char[wh.pattern.length()+1];
            strcpy((char*)con->rhsValue.data, wh.pattern.data());
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

int appendRel(char* &p, const char* q)
{
    if(p == NULL)
    {
        p = new char[strlen(q)+1];
        strcpy(p, q);
        return 0;
    }
    else if(strcmp(p, q)) return QL_RELNOTEXIST;
    return 0;
}

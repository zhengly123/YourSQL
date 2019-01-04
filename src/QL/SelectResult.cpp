//
// Created by eric on 18-12-30.
//

#include <algorithm>
#include <cstring>
#include "SelectResult.h"

SelectResult::SelectResult(Printer *printer, std::string relName, int nSelAttrs, const RelAttr *selAttrs, int nConditions,
                           const Condition *conditions)
                           :printer(printer)
{
    for (int i = 0; i < nSelAttrs; ++i)
    {
        if (relName == std::string(selAttrs[i].relName) && !setRelAttrExist(selAttrs[i]))
            targetRelAttrs.push_back(selAttrs[i]);
    }
    for (int i = 0; i < nConditions; ++i)
    {
        if (conditions->bRhsIsAttr)
        {
            if (relName == std::string(conditions->lhsAttr.relName) &&
                !setRelAttrExist(conditions->lhsAttr))
            {
                targetRelAttrs.push_back(conditions->lhsAttr);
            }
            if (relName == std::string(conditions->rhsAttr.relName) &&
                !setRelAttrExist(conditions->rhsAttr))
            {
                targetRelAttrs.push_back(conditions->rhsAttr);
            }
        }
    }
}

bool SelectResult::setRelAttrExist(RelAttr relAttr)
{
    return std::find_if(targetRelAttrs.begin(), targetRelAttrs.end(),
                        [relAttr](RelAttr t) {
                            return strcmp(t.relName, relAttr.relName) == 0 &&
                                   strcmp(t.attrName, relAttr.attrName) == 0 &&
                                   t.op == relAttr.op;
                        }) != targetRelAttrs.end();
}

RC SelectResult::insert(const char *relName, Selector &selector, vector<AttrInfo> tableAttrs)
{
    RM_Record record;
    RM_FileHandle *handle = nullptr;
    RID rid;
    int cnt = 0;
    int i = 0;
    vector<int> usedAttrIndexes;
    for (auto attr:tableAttrs)
    {
        // relAttr only store pointer which is dangerous to use in other function
        RelAttr relAttr;
        relAttr.relName = const_cast<char *>(relName);
        relAttr.attrName = attr.attrName;
        for(int j = 0; j < 5; ++ j) // TODO: 5
        {
            relAttr.op = j;
            if (setRelAttrExist(relAttr))
            {
//            dataRelAttr.push_back(relAttr);
//            strcpy(attr.relName, relName);
                attr.aggregateFunc = j;
                dataAttrInfos.push_back(attr);
                usedAttrIndexes.push_back(i);
            }
        }
        ++i;
    }
    // if no attr is selected, insert a null data
    if (usedAttrIndexes.empty())
    {
        dataList.push_back(vector<DataType>());
        return 0;
    }
    while (selector.getNext(record, handle))
    {
        char *data;
        record.GetData(data);
        cnt++;
        vector<DataType> dataVector;
        for (auto i:usedAttrIndexes)
        {
            DataType dataItem(data + tableAttrs[i].offset,
                              data + tableAttrs[i].offset + tableAttrs[i].attrLength);
            dataItem.push_back(*(data + tableAttrs[i].nullOffset));
            dataVector.push_back(dataItem);
        }
        dataList.push_back(dataVector);
    }
    return 0;
}

SelectResult operator*(SelectResult lhs, SelectResult rhs)
{
    using DataType=std::vector<char>;
    SelectResult result{lhs};
//    result.dataRelAttr.insert(result.dataRelAttr.end(), rhs.dataRelAttr.begin(),
//                              rhs.dataRelAttr.end());
    result.dataAttrInfos.insert(result.dataAttrInfos.end(), rhs.dataAttrInfos.begin(),
                              rhs.dataAttrInfos.end());
    result.dataList.clear();
    for (auto ld:lhs.dataList)
    {
        for (auto rd:rhs.dataList)
        {
            vector<DataType> dataVector{ld};
            dataVector.insert(dataVector.end(), rd.begin(), rd.end());
            result.dataList.push_back(dataVector);
        }
    }
    return result;
}

void SelectResult::filter(int nConditions, const Condition *conditions)
{
    for (int i = 0; i < nConditions; ++i)
    {
        if (!conditions[i].bRhsIsAttr)
            continue;

        if (isRelAttrIndexExist(conditions->lhsAttr) &&
            isRelAttrIndexExist(conditions->rhsAttr))
        {
            int lIndex = getRelAttrIndex(conditions->lhsAttr);
            int rIndex = getRelAttrIndex(conditions->rhsAttr);
            auto it = dataList.begin();
            int cnt=0;
            while (it != dataList.end())
            {
                char *lData = (*it)[lIndex].data();
                char *rData = (*it)[rIndex].data();
                // TODO: two null compare????
                // the condition must be a two-attr comparision
                if (!Cmp(lData, rData, conditions->op, dataAttrInfos[i].attrType))
                {
                    dataList.erase(it++);
                    ++cnt;
                } else
                {
                    ++it;
                }
            }
            printf("DEBUG: filter out %d tuples\n", cnt);
        }
    }
}

int SelectResult::getRelAttrIndex(RelAttr relAttr)
{
    int ret = (int) std::distance(dataAttrInfos.begin(),
                                  std::find_if(dataAttrInfos.begin(), dataAttrInfos.end(),
                                               [relAttr](AttrInfo t) {
                                                   return strcmp(t.relName, relAttr.relName) == 0 &&
                                                          strcmp(t.attrName, relAttr.attrName) == 0 &&
                                                           t.aggregateFunc == relAttr.op;
                                               }));

    if(ret == dataAttrInfos.size()) return -1;
    assert(ret<dataAttrInfos.size());
    return ret;
}

void SelectResult::setUnit()
{
    dataList.clear();
    dataList.push_back(vector<DataType>());
}

void SelectResult::print(int nSelAttrs, const RelAttr *selAttrs)
{
    std::vector<int> indexes;
    for (int i = 0; i < nSelAttrs; ++i)
    {
        indexes.push_back(getRelAttrIndex(selAttrs[i]));
    }

    for (auto dataVector: conlist)
    {
        for (int i=0;i<nSelAttrs;++i)
        {
            int index=indexes[i];
            printer->PrintValue(dataVector[index].data(), dataVector[index].back(),
                                dataAttrInfos[index].attrType);
        }
        printer->Println();
    }
}

RC SelectResult::applyConstraint(int natt, RelAttr att[], int ngrp, const RelAttr grp[], int nord, const RelAttr ord[])
{
    // Validate

    for(int i = 0; i < ngrp; ++ i)
        if(getRelAttrIndex(grp[i]) < 0) return QL_AttrNotExist;

    for(int i = 0; i < nord; ++ i)
        if(getRelAttrIndex(ord[i]) < 0) return QL_AttrNotExist;

    int attrlen = dataAttrInfos.size();
    int noAggregateFunc = 0;

    //if(natt != attrlen) return QL_INVALIDSIZE;

    for(int i = 0; i < natt; ++ i)
        if(att[i].op == 0) noAggregateFunc ++; // No Aggregate Function Must be Group By

    if(noAggregateFunc < natt && ngrp != noAggregateFunc) return QL_GROUPBYERR;

    // In order to permit no group collective operation, comment out the following
//    if(ngrp == 0)
//    {
//        // No group : Normal Exit
//        conlist.clear();
//
//        for(auto dataVec : dataList) conlist.push_back(dataVec);
//    }
//    else
    {
        // Handle AVG

        int total = natt;
        char* dataone = new char[4];
        *(int*)dataone = 1;
        char datazero = 0;

        vector<int> avgLink;
        vector<int> indexes;
        vector<char> one(dataone, dataone + 4);

        avgLink.clear();
        indexes.clear();
        one.push_back(datazero);

        for (int i = 0; i < natt; ++i)
            indexes.push_back(getRelAttrIndex(att[i]));

        for(int i = 0; i < natt; ++ i)
            if(att[i].op == AGGREGATE_AVG)
            {
                if(dataAttrInfos[indexes[i]].attrType != INT &&
                   dataAttrInfos[indexes[i]].attrType != FLOAT) return QL_WRONGAVGTYPE;
                avgLink.push_back(total++);
            }
            else avgLink.push_back(0);

        conlist.clear();
        grplist.clear();

        for(auto dataVec : dataList)
        {
            // add avg column
            for(int i = natt; i < total; ++ i)
                dataVec.push_back(one);

            // check group by attrs
            vector<vector<char>> Grpvec = dataVec;

            // clear the non-aggregate func column
            for(int i = 0; i < natt; ++ i) if(att[i].op != 0) Grpvec[indexes[i]].clear();

            // find the data vector
            vector<vector<vector<char>>>::iterator it;
            it = std::find(grplist.begin(), grplist.end(), Grpvec);

            if(it == grplist.end())
            {
                grplist.push_back(Grpvec);
                conlist.push_back(dataVec);
            }
            else
            {
                int d = it - grplist.begin();
                for(int i = 0; i < natt; ++ i)
                {
                    int id = indexes[i];
                    switch(att[i].op)
                    {
                        case AGGREGATE_SUM : Tadd(conlist[d][id].data(), dataVec[id].data(), dataAttrInfos[id].attrType); break;
                        case AGGREGATE_MAX : Tmax(conlist[d][id].data(), dataVec[id].data(), dataAttrInfos[id].attrType); break;
                        case AGGREGATE_MIN : Tmin(conlist[d][id].data(), dataVec[id].data(), dataAttrInfos[id].attrType); break;
                        case AGGREGATE_AVG : Tadd(conlist[d][id].data(), dataVec[id].data(), dataAttrInfos[id].attrType);
                                             Tadd(conlist[d][avgLink[i]].data(), dataVec[avgLink[i]].data(), INT); break;
                        default: break;
                    }
                }
            }
        }

        // Handle AVG
        if(total > natt)
        {
            char * resbuf = new char[4];
            vector<char> newres;

            for(int p = 0; p < conlist.size(); ++ p)
            {
                for(int i = 0; i < natt; ++ i)
                    if(att[i].op == AGGREGATE_AVG)
                    {
                        int j = indexes[i];
                        int k = avgLink[i];
                        if(dataAttrInfos[j].attrType == INT)
                        {
                            int a = *(int*)conlist[p][j].data();
                            int b = *(int*)conlist[p][k].data();
                            *(float*) resbuf = float(a) / float(b);

                            newres.clear();
                            for(int i = 0; i <= 3; ++ i) newres.push_back(resbuf[i]);
                            newres.push_back(datazero);

                            conlist[p][j] = newres;
                        }
                        else if(dataAttrInfos[j].attrType == FLOAT)
                        {
                            float a = *(float*)conlist[p].data();
                            float b = *(float*)conlist[p].data();
                            *(float*) resbuf = a / b;

                            newres.clear();
                            for(int i = 0; i <= 3; ++ i) newres.push_back(resbuf[i]);
                            newres.push_back(datazero);

                            conlist[p][j] = newres;
                        }
                        else return QL_WRONGAVGTYPE;
                    }

                // Remove Cnt Column
                for(int i = natt; i < total; ++ i)
                    conlist[p].pop_back();
            }

            for(int i = 0; i < natt; ++ i)
                if(att[i].op == AGGREGATE_AVG)
                    if(dataAttrInfos[indexes[i]].attrType == INT)
                        dataAttrInfos[indexes[i]].attrType = FLOAT;

        }

    }


    if(nord)
    {
        orderType.clear();
        orderIndex.clear();
        orderSig.clear();

        for(int i = 0; i < nord; ++ i)
        {
            int index = getRelAttrIndex(ord[i]);
            orderIndex.push_back(index);
            orderType.push_back(dataAttrInfos[index].attrType);
            orderSig.push_back(ord[i].ord);
        }

        OrderByCompare ordercmp(orderIndex, orderType, orderSig);
        sort(conlist.begin(), conlist.end(), ordercmp);
    }

    return 0;
}


OrderByCompare :: OrderByCompare(vector<int> ordindex, vector<AttrType> ordtype, vector<int> ordsig)
{
    ordIndex = ordindex;
    ordType = ordtype;
    ordSig = ordsig;
}

bool OrderByCompare :: operator() (vector<vector<char>> a, vector<vector<char>> b)
{
    for(int i = 0; i < ordType.size(); ++ i)
    {
        int index = ordIndex[i];
        AttrType typ = ordType[i];
        int if_eq = Cmp(a[index].data(), b[index].data(), EQ_OP, typ);
        if(if_eq) continue;
        int if_lt = Cmp(a[index].data(), b[index].data(), LT_OP, typ);
        return if_lt ^ (ordSig[i] == ORD_DEC);
    }
}


bool SelectResult::isRelAttrIndexExist(RelAttr relAttr)
{
    return dataAttrInfos.begin(),
            std::find_if(dataAttrInfos.begin(), dataAttrInfos.end(),
                         [relAttr](AttrInfo t) {
                             return strcmp(t.relName, relAttr.relName) == 0 &&
                                    strcmp(t.attrName, relAttr.attrName) == 0 &&
                                     t.aggregateFunc == relAttr.op;
                         }) != dataAttrInfos.end();
}

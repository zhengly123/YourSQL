//
// Created by eric on 18-12-30.
//

#ifndef YOURSQL_SELECTRESULT_H
#define YOURSQL_SELECTRESULT_H

#include <vector>
#include <list>
#include "../IX/IX_PRIVATE.h"
#include "QL_PUBLIC.h"
#include "../SM/SM_PUBLIC.h"
#include "SelectResult.h"
#include "Selector.h"

class OrderByCompare
{
public:
    vector<int> ordIndex, ordSig;
    vector<AttrType> ordType;
    OrderByCompare(vector<int>, vector<AttrType>, vector<int>);
    bool operator() (vector<vector<char>> a, vector<vector<char>> b);
};

class SelectResult
{
public:
    using DataType = std::vector<char>;

    SelectResult(Printer *printer, std::string relName, int nSelAttrs, const RelAttr selAttrs[],
                 int nConditions, const Condition conditions[]);
    RC insert(const char *relName, Selector &selector, vector<AttrInfo> tableAttrs);

    friend SelectResult operator *(SelectResult lhs, SelectResult rhs);

    void filter(int nConditions, const Condition conditions[]);

    void setUnit();

    /**
     * apply group by, order by constraint to the result
     * @param ngrp  group by cnt
     * @param grp   group by attr
     * @param nord  order by cnt
     * @param ord   order bt attr
     * @return Error code. 0 stands for correct.
     */
    RC applyConstraint(int natt, RelAttr att[], int ngrp, const RelAttr grp[], int nord, const RelAttr ord[]);

    int orderBySort(vector<DataType>, vector<DataType>);

    void print(int nSelAttrs, const RelAttr selAttrs[]);

private:
    Printer *printer;

    vector<AttrInfo> dataAttrInfos; // meta data of columns

    list<vector<DataType>> dataList; //last char is null flag

    vector<vector<DataType>> conlist; // temp list used in applyConstraint
    vector<vector<DataType>> grplist; // temp list used in applyConstraint

    vector<RelAttr> targetRelAttrs; // attrs which should be inserted

    vector<int>     orderIndex, orderSig;
    vector<AttrType> orderType;

    /**
     * Whether an attribute should be saved when filter data from file.
     * NOT used for search a attribute in dataAttrInfos(dataList).
     * @param relAttr
     * @return
     */
    bool setRelAttrExist(RelAttr relAttr);

    /**
     * Check whether an attribute is in dataAttrInfos(dataList).
     * @param relAttr
     * @return
     */
    bool isRelAttrIndexExist(RelAttr relAttr);
    /**
     * Get index of an attribute in dataAttrInfos(dataList).
     * @param relAttr
     * @return
     * @attention It is assumed that *relAttr* exists in the dataAttrInfos(dataList).
     * Otherwise, program will be aborted.
     */
    int getRelAttrIndex(RelAttr relAttr);
};


#endif //YOURSQL_SELECTRESULT_H

//
// Created by eric on 18-12-30.
//

#ifndef YOURSQL_SELECTRESULT_H
#define YOURSQL_SELECTRESULT_H

#include <vector>
#include <list>
#include "../IX/IX_PRIVATE.h"
//#include "../QL/QL_PUBLIC.h"
#include "../SM/SM_PUBLIC.h"
#include "SelectResult.h"
#include "Selector.h"
class SelectResult
{
public:
    SelectResult(Printer *printer, std::string relName, int nSelAttrs, const RelAttr selAttrs[],
                 int nConditions, const Condition conditions[]);
    RC insert(const char *relName, Selector &selector, vector<AttrInfo> tableAttrs);
    friend SelectResult operator *(SelectResult lhs, SelectResult rhs);
    void filter(int nConditions, const Condition conditions[]);
    void setUnit();
    void print(int nSelAttrs, const RelAttr selAttrs[]);
//    int size();
private:
    Printer *printer;
    using DataType=std::vector<char>;
//    vector<RelAttr> dataRelAttr;
    vector<AttrInfo> dataAttrInfos;
    list<vector<DataType>> dataList; //last char is null flag


    vector<RelAttr> targetRelAttrs; // attrs which should be inserted
    bool setRelAttrExist(RelAttr relAttr);
    int getRelAttrIndex(RelAttr relAttr);
};


#endif //YOURSQL_SELECTRESULT_H

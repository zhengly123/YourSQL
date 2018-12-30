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
    auto k= std::find_if(targetRelAttrs.begin(), targetRelAttrs.end(),
                        [relAttr](RelAttr t) {
                            return strcmp(t.relName, relAttr.relName) == 0 &&
                                   strcmp(t.attrName, relAttr.attrName) == 0;
                        }) != targetRelAttrs.end();
    return k;
    return std::find_if(targetRelAttrs.begin(), targetRelAttrs.end(),
                        [relAttr](RelAttr t) {
                            return strcmp(t.relName, relAttr.relName) == 0 &&
                                   strcmp(t.attrName, relAttr.attrName) == 0;
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
        if (setRelAttrExist(relAttr))
        {
//            dataRelAttr.push_back(relAttr);
//            strcpy(attr.relName, relName);
            dataAttrInfos.push_back(attr);
            usedAttrIndexes.push_back(i);
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
                                                          strcmp(t.attrName, relAttr.attrName) == 0;
                                               }));

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

    for (auto dataVector: dataList)
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

bool SelectResult::isRelAttrIndexExist(RelAttr relAttr)
{
    return dataAttrInfos.begin(),
            std::find_if(dataAttrInfos.begin(), dataAttrInfos.end(),
                         [relAttr](AttrInfo t) {
                             return strcmp(t.relName, relAttr.relName) == 0 &&
                                    strcmp(t.attrName, relAttr.attrName) == 0;
                         }) != dataAttrInfos.end();
}

//
// Created by eric on 18-12-28.
//

#include <cstring>
#include <algorithm>
#include "Selector.h"
#include "QL_PUBLIC.h"

Selector::Selector(IX_Manager *ixm, RM_Manager *rmm, const char *relName,
                   RelationMeta relmeta,
                   vector<AttrInfo> attributes, int nConditions, const Condition *conditions)
        : dead(false), errorReason(0), errorIndex(0)
{

    this->ixm = ixm;
    this->rmm = rmm;
    this->relmeta = relmeta;
    this->attrs = attributes;
    for (int i = 0; i < nConditions; ++i)
    {
        this->conditions.push_back(conditions[i]);
    }
    rmm->OpenFile(relToFileName(relName).data(), handle);
    if (!checkConditionLegal())
    {
        dead=true;
        return;
    }
    iterateOptimize();
}

void Selector::iterateOptimize()
{
    void *data;
    scan.OpenScan(handle,AttrType::INT, 0, 0, NO_OP, data);
}

int Selector::getNext(RM_Record &outRecord, RM_FileHandle *&outHandle)
{
    assert(!dead);
    RM_Record record;
    while (scan.GetNextRec(record) != RM_EOF)
    {
//        int i;
//        for (int i = 0; i < conditions.size(); ++i)
//        {
//            if ()
//        }
        auto it=conditions.begin();
        for (; it != conditions.end(); ++it)
        {
            if (!checkCondition(*it, record.GetData()))
                break;
        }
        if (it == conditions.end())
        {
            outRecord = record;
            outHandle = &handle;
            return 1;
        }
    }
    dead = true;
    return 0;
}

auto Selector::checkAttrExist(char *attrName)
{
    return std::find_if(attrs.begin(), attrs.end(),
                        [attrName](AttrInfo const &a) {
                            return strcmp(attrName, a.attrName) == 0;
                        });
}

bool Selector::checkConditionLegal()
{
    int i;
    for (i=0;i<conditions.size();++i)
    {
        const auto& cond=conditions[i];
        // 1
        if (cond.lhsAttr.relName!= nullptr)
        {
            errorReason = QL_RELNOTNULL;
            break;
        }
        //
        auto it = checkAttrExist(cond.lhsAttr.attrName);
        if (it == attrs.end())
        {
            errorReason = QL_ATTRNOTFIND;
            break;
        }
        AttrInfo attrL = *it;
//        lhsAttrs.push_back(attrL);
        if (cond.flag)
        {
            // cond is null of not null
        } else if (cond.bRhsIsAttr)
        {
            it = checkAttrExist(cond.rhsAttr.attrName);
            if (it == attrs.end())
            {
                errorReason = QL_ATTRNOTFIND;
                break;
            }
            AttrInfo attrR = *it;
            if (attrL.attrType != attrR.attrType)
            {
                errorReason = QL_TYPEUNMATCHED;
                break;
            }
        } else// if rhs is a value
        {
            if (attrL.attrType!=cond.rhsValue.type)
            {
                errorReason = QL_TYPEUNMATCHED;
                break;
            }
        }
    }
    if (i < conditions.size())
    {
        errorIndex=i;
        return false;
    }
    else
        return true;
}

bool Selector::checkCondition(Condition cond, void *data)
{
    char *leftValue, *rightValue;
    AttrInfo attrL = *checkAttrExist(cond.lhsAttr.attrName);
    leftValue=(char*)data+attrL.offset;
    if (cond.flag==IsNull)
    {
        return (*((char*)data + attrL.nullOffset) != 0);
    } else if (cond.flag == IsNotNull)
    {
        return (*((char*)data + attrL.nullOffset) == 0);
    } else
    {
        if (cond.bRhsIsAttr)
        {
            AttrInfo attrR = *checkAttrExist(cond.rhsAttr.relName);
            rightValue=(char*)data+attrR.offset;
        }
        else
            rightValue=(char *)cond.rhsValue.data;
        return Cmp(leftValue, rightValue, cond.op, attrL.attrType);
    }
}

Selector::~Selector()
{
    scan.CloseScan();
    rmm->CloseFile(handle);
}

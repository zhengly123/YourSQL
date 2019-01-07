//
// Created by eric on 18-12-28.
//

#include <cstring>
#include <algorithm>
#include "Selector.h"
#include "QL_PUBLIC.h"

Selector::Selector(IX_Manager *ixm, RM_Manager *rmm, SM_Manager *smm, const char *relName,
                   RelationMeta relmeta, vector<AttrInfo> attributes,
                   int nConditions, const Condition *conditions, RM_FileHandle SMhandle, bool interTable)
        : dead(false), errorReason(0), errorIndex(0), enableIndex(false)
{

    this->ixm = ixm;
    this->rmm = rmm;
    this->smm = smm;
    this->relmeta = relmeta;
    this->attrs = attributes;
    for (int i = 0; i < nConditions; ++i)
    {
        if (interTable)
        {
            Condition cond = conditions[i];
            // this should be forbid in parser
            assert(cond.skip==false);
            if (cond.lhsAttr.relName == nullptr)
            {
                errorReason = QL_RELNULL;
                errorIndex = i;
                dead = true;
                assert(0);
            }
            // skip if cond relates to other table
            if (strcmp(cond.lhsAttr.relName, relName) != 0
                || (cond.bRhsIsAttr && strcmp(cond.rhsAttr.relName, relName) != 0))
            {
                cond.skip = true;
                this->conditions.push_back(cond);
            } else
            {
                cond.lhsAttr.relName = cond.rhsAttr.relName = nullptr;
                this->conditions.push_back(cond);
            }
        } else
        {
            this->conditions.push_back(conditions[i]);
        }
    }
    //rmm->OpenFile(relToFileName(relName).data(), handle);
    handle = SMhandle;
    if (!checkConditionLegal())
    {
        dead=true;
        return;
    }
    iterateOptimize(relName, nConditions, conditions);
}

void Selector::iterateOptimize(const char *relName, int nCondition, const Condition *conditions)
{
    assert(!enableIndex);
    std::vector<std::pair<int, int>> indexList;
    for (int i = 0; i < nCondition; ++i)
    {
        const Condition &cond = conditions[i];
        // In multiple tables selection, check relName is necessary.
        if ((!cond.lhsAttr.relName || strcmp(relName, cond.lhsAttr.relName) == 0) &&
            !cond.bRhsIsAttr && cond.flag == CondType::COND_NORMAL)
        {
            const AttrInfo attrInfo = getAttr(cond.lhsAttr.attrName);
            if (attrInfo.indexNum)
            {
                // store selectivity of each attributes
                IX_IndexHandle *tempIndexHandle = smm->indexhandleGet(
                        std::string(attrInfo.relName), attrInfo.indexNum);
                indexList.emplace_back(make_pair(tempIndexHandle->getCntNode(), i));
            }
        }
    }
//    if (false)
    // If there are available indexes
    if (!indexList.empty())
    {
        sort(indexList.begin(), indexList.end());
        // choose index of which condition
        int i = indexList.back().second;
        assert(i>=0);
        assert(i<nCondition);
        const Condition &cond = conditions[i];
        assert(!cond.bRhsIsAttr);
        const AttrInfo attrInfo = getAttr(cond.lhsAttr.attrName);
        assert(attrInfo.indexNum);
        fprintf(stderr, "Debug: use index no %d\n", attrInfo.indexNum);
        enableIndex = true;
        attrWithIndex=string(attrInfo.attrName);
        RC rc;
        //rc = ixm->OpenIndex(attrInfo.relName, attrInfo.indexNum, indexHandle);
        //assert(rc == 0);
        indexHandle = smm->indexhandleGet(std::string(attrInfo.relName), attrInfo.indexNum);
        rc = indexScan.OpenScan(*indexHandle, cond.op, cond.rhsValue.data);
        assert(rc == 0);
#ifdef OutputLinearIndex
        //debug
                printf("DEBUG: iterateOptimize\n");
                indexHandle->printLinearLeaves();
#endif
    }
    else
    {
        void *data = nullptr;
        scan.OpenScan(handle, AttrType::INT, 0, 0, NO_OP, data);
    }
}

int Selector::getNext(RM_Record &outRecord, RM_FileHandle *&outHandle)
{
    assert(!dead);
    RM_Record record;
    if (!enableIndex)
    {
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
    } else
    {
        RID rid;
        while (indexScan.GetNextEntry(rid) != IX_ITERATOR_TO_END)
        {
            handle.GetRec(rid, record);
            auto it=conditions.begin();
            for (; it != conditions.end(); ++it)
            {
                if (!checkCondition(*it, record.GetData()))
                    break;
            }
            // need to close??
            if (it == conditions.end())
            {
                outRecord = record;
                outHandle = &handle;
                return 1;
            }
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
    assert(dead == false);
    int i;
    for (i=0;i<conditions.size();++i)
    {
        const auto& cond=conditions[i];
        if (cond.skip)
            continue;
        // 1
        //if (cond.lhsAttr.relName!= nullptr)
        //{
        //    errorReason = QL_RELNOTNULL;
        //    break;
        //}
        //
        auto it = checkAttrExist(cond.lhsAttr.attrName);
        if (it == attrs.end())
        {
            errorReason = QL_AttrNotExist;
            break;
        }
        AttrInfo attrL = *it;
//        lhsAttrs.push_back(attrL);
        if (cond.flag != CondType::COND_NORMAL)
        {
            // cond is null of not null
        } else if (cond.bRhsIsAttr)
        {
            it = checkAttrExist(cond.rhsAttr.attrName);
            if (it == attrs.end())
            {
                errorReason = QL_AttrNotExist;
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
    if (cond.skip)
        return true;
    char *leftValue, *rightValue;
    AttrInfo attrL = *checkAttrExist(cond.lhsAttr.attrName);
    leftValue=(char*)data+attrL.offset;
    if (cond.flag == CondType::COND_ISNULL)
    {
        return (*((char*)data + attrL.nullOffset) != 0);
    } else if (cond.flag == CondType::COND_NOTNULL)
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
    if (!enableIndex)
    {
        scan.CloseScan();
    } else
    {
        indexScan.CloseScan();
        //ixm->CloseIndex(indexHandle);
    }
    //rmm->CloseFile(handle);
}

bool Selector::checkSetLegal(const int nSet, const Condition sets[])
{
    int i;
    std::vector<Condition> conditions;
    for (int i = 0; i < nSet; ++i)
    {
        conditions.push_back(sets[i]);
    }
    for (i=0;i<conditions.size();++i)
    {
        const auto& cond=conditions[i];
        // 1
        //if (cond.lhsAttr.relName!= nullptr)
        //{
        //    errorReason = QL_RELNOTNULL;
        //    break;
        //}
        //
        auto it = checkAttrExist(cond.lhsAttr.attrName);
        if (it == attrs.end())
        {
            errorReason = QL_AttrNotExist;
            break;
        }
        AttrInfo attrL = *it;
//        lhsAttrs.push_back(attrL);
        if (cond.flag != CondType::COND_NORMAL)
        {
            // IsNotNull cannot be accepted here
            assert(0);
        } else if (cond.bRhsIsAttr)
        {
            errorReason = QL_VALUE_EQPECTED;
            break;
        } else// if rhs is a value
        {
            if (cond.rhsValue.type == AttrType::NULLTYPE)
            {
                if (attrL.isNotNull())
                    errorReason = QL_ATTRNOTNULL;
            } else if (attrL.attrType != cond.rhsValue.type)
            {
                errorReason = QL_TYPEUNMATCHED;
                break;
            }
        }

        if(cond.flag == CondType::COND_NORMAL)
        {
            if(cond.op == CompOp::LK_OP || cond.op == CompOp::UKL_OP)
            {
                if(attrL.attrType != AttrType::STRING)
                    errorReason = QL_TYPEUNMATCHED;
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

AttrInfo Selector::getAttr(char *attr)
{
    return *checkAttrExist(attr);
}

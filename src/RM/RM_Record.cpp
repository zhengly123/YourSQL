//
// Created by 杨乐 on 2018/11/4.
//

#include "rm_internal.h"
#include "rm.h"


/*
 * Constructor
 */
RM_Record::RM_Record()
        : pData(), rid(0, 0)
{

}

/*
 * Destructor
 */
RM_Record :: ~RM_Record ()
{
}

/*
 * Set pData to point to the record's contents
 */
RC RM_Record :: GetData    (char *&pData) const
{
    pData = this->pData.get();
    return 0;
}

/*
 * Get the record id
 */
RC RM_Record :: GetRid     (RID &rid) const
{
    rid = this->rid;
    return 0;
}
/*
 * Set pData to point to the record's contents
 */
RC RM_Record::SetData(std::shared_ptr<char> pData)
//RC RM_Record :: SetData    (char *pData)
{
    this->pData = pData;
    return 0;
}

/*
 *
 */
RC RM_Record :: SetRid     (RID rid)
{
    this->rid = rid;
    return 0;
}

void *RM_Record::GetData() const
{
    return this->pData.get();
}


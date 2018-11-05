//
// Created by 杨乐 on 2018/11/4.
//

#include "rm_internal.h"

/*
 * Constructor
 */
RM_Record :: RM_Record  ()
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
    return 0;
}

/*
 * Get the record id
 */
RC RM_Record :: GetRid     (RID &rid) const
{
    return 0;
}
/*
 * Set pData to point to the record's contents
 */
RC RM_Record :: SetData    (char *pData) const
{
    return 0;
}

/*
 *
 */
RC RM_Record :: SetRid     (RID rid) const
{
    return 0;
}


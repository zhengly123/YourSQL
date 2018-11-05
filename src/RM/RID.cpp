//
// Created by 杨乐 on 2018/11/4.
//

#include "rm_internal.h"

/*
 * Default constructor
 */
RID :: RID        ()
{

}

/*
 * Destructor
 */
RID :: ~RID       ()
{

}

/*
 * Construct RID from page and slot number
 */


/*
 * Set RID from page and slot number
 */
RC RID :: Set        (PageNum pageNum, SlotNum slotNum)
{
    this->pageNum = pageNum;
    this->slotNum = slotNum;
    return 0;
}

/*
 * Return page number
 */
RC RID :: GetPageNum (PageNum &pageNum) const
{
    pageNum = this->pageNum;

    return 0;
}

/*
 * Return slot number
 */
RC RID :: GetSlotNum (SlotNum &slotNum) const
{
    slotNum = this->slotNum;

    return 0;
}

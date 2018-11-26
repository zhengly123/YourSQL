//
// Created by 杨乐 on 2018/11/4.
//

#include "rm_internal.h"
#include "rm.h"


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

bool RID::operator==(RID &b) const
{
    PageNum p;
    int s;
    b.GetPageNum(p);
    b.GetSlotNum(s);
    return pageNum==p && slotNum==s;
}

PageNum RID::GetPageNum() const
{
    return pageNum;
}

SlotNum RID::GetSlotNum() const
{
    return slotNum;
}

RC RID::SetPageNum(PageNum pageNum)
{
    this->pageNum=pageNum;
}

RC RID::SetSlotNum(SlotNum slotNum)
{
    this->slotNum=slotNum;
}

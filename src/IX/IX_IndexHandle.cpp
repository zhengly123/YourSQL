//
// Created by eric on 18-11-26.
//

#include <cstring>
#include "IX_IndexHandle.h"

RC IX_IndexHandle::open(FileManager &fm, BufPageManager &bpm,
                        IX_Manager &ixManager, int fileID)
{
    this->fm = &fm;
    this->bpm=&bpm;
    this->ixManager=&ixManager;
    this->ixHeader=ixHeader;
    this->fileID = fileID;
    int index;
    IX_Header ixHeader;
    BufType b = bpm.getPage(fileID, 0, index);
    memcpy(&ixHeader, b, sizeof(ixHeader));
    bpm.access(index);
    return 0;
}

void IX_IndexHandle::getFileID(int &fileID)
{
    fileID = this->fileID;
}

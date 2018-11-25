//
// Created by eric on 18-11-26.
//

#include <sstream>
#include "IX_Manager.h"

IX_Manager::IX_Manager(FileManager &pfm)
:fileManager(pfm)
{

}

IX_Manager::~IX_Manager()
{

}

RC IX_Manager::CreateIndex(const char *fileName, int indexNo, AttrType attrType, int attrLength)
{
    if (indexNo<0)
    {
        return IX_INVALID_INDEXNO;
    }
    string rankFileName;
    std::ostringstream oss(rankFileName);
    oss<<fileName<<"."<<indexNo<<".i";
    //TODO: open file with pm and write head

    return 0;
}

RC IX_Manager::OpenIndex(const char *fileName, int indexNo, IX_IndexHandle &indexHandle)
{
    return 0;
}

RC IX_Manager::CloseIndex(IX_IndexHandle &indexHandle)
{
    return 0;
}

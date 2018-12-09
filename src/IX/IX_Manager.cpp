//
// Created by eric on 18-11-26.
//

#include <sstream>
#include <cstring>
#include <cassert>
#include "IX_Manager.h"

IX_Manager::IX_Manager(FileManager &pfm, BufPageManager &bpm)
        : fm(pfm), bpm(bpm)
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
    string rankFileName = getFileNameWithIndex(fileName, indexNo);
    // Creating new rank file
    fm.createFile(rankFileName.data());

    // Open the file
    int fileID, index;
    assert(fm.openFile(rankFileName.data(), fileID));

    // #0 : file header
    BufType b = bpm.allocPage(fileID, 0, index, false);

    IX_Header ixHeader;
    ixHeader.pageNum=1;
    ixHeader.pageSize=PAGE_SIZE;
    ixHeader.rootPage=-1;
    ixHeader.indexPairSize = attrLength + sizeof(RID);
    ixHeader.attrType=attrType;
    ixHeader.attrLength=attrLength;
    memcpy(b, &ixHeader, sizeof(ixHeader));

    bpm.markDirty(index);

    // #1 : initial data page
    b = bpm.allocPage(fileID, 1, index, false);

    memset(b, 0, PAGE_SIZE); // refresh the page

    bpm.markDirty(index);
    bpm.close();
    fm.closeFile(fileID);

    return 0;
}

RC IX_Manager::OpenIndex(const char *fileName, int indexNo, IX_IndexHandle &indexHandle)
{
    int fileID;
    string rankFileName = getFileNameWithIndex(fileName, indexNo);
    //TODO: file not exist test
    fm.openFile(rankFileName.data(), fileID);

    // if index has been already opened
    if (openedFile.count(make_pair(string(fileName), indexNo)))
    {
        return IX_INDEX_OPENED;
    }
    openedFile[make_pair(string(fileName), indexNo)]= fileID;

    // Set the necessary message to fileHandle
    indexHandle.open(fm, bpm, *this, fileID);

    return 0;
}

RC IX_Manager::CloseIndex(IX_IndexHandle &indexHandle)
{
    int fileID;
    indexHandle.getFileID(fileID);
    bpm.close();
    fm.closeFile(fileID);
    return 0;
}

string IX_Manager::getFileNameWithIndex(const char* fileName, int indexNum)
{
    std::ostringstream oss;
    oss<<fileName<<"."<<indexNum<<".i";
    return oss.str();
}

RC IX_Manager::DestroyIndex(const char *fileName, int indexNo)
{
//    int fileID = openedFile[make_pair(string(fileName), indexNo)];
//    bpm.close();
//    fm.closeFile(fileID);
    if (openedFile.count(make_pair(string(fileName), indexNo)))
    {
        return IX_INDEX_OPENED;
    }
    //TODO: fm.DestoryFile
    //pf system 中并没有提供这样的接口，需要新增加这个API
    return 0;
}

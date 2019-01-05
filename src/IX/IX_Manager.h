//
// Created by eric on 18-11-26.
//

#pragma once
#ifndef YOURSQL_IX_MANAGER_H
#define YOURSQL_IX_MANAGER_H

#include <string>
#include <map>
#include "IX_PRIVATE.h"
#include "IX_PUBLIC.h"
#include "../RM/rm.h"
using namespace std;

class IX_Manager {
public:
    IX_Manager   (FileManager &pfm, BufPageManager &bpm);              // Constructor
    ~IX_Manager  ();                             // Destructor
    /**
     * 创建文件并返回。
     * @param fileName  需要创建index的文件名字。
     * @param indexNo   一个非负数，可用作index文件区别。
     * @param attrType
     * @param attrLength
     * @return
     */
    RC CreateIndex  (const char *fileName,          // Create new index
                     int        indexNo,
                     AttrType   attrType,
                     int        attrLength);
    RC DestroyIndex (const char *relName,          // Destroy index
                     int        indexNo);
    /**
     * 打开一个索引文件，返回对应的idl(valid).
     * @param relName
     * @param indexNo
     * @param indexHandle
     * @return
     */
    RC OpenIndex    (const char *relName,          // Open index
                     int        indexNo,
                     IX_IndexHandle &indexHandle);
    RC CloseIndex   (IX_IndexHandle &indexHandle);  // Close index
private:
    FileManager &fm;
    BufPageManager  &bpm;
    map<pair<string, int>, int> openedFile;

    string getFileNameWithIndex(const char* fileName, int indexNum);
};

#endif //YOURSQL_IX_MANAGER_H

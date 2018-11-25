//
// Created by eric on 18-11-26.
//

#ifndef YOURSQL_IX_MANAGER_H
#define YOURSQL_IX_MANAGER_H

#include "../RM/rm.h"
#include "IX_PRIVATE.h"

class IX_Manager {
public:
    IX_Manager   (FileManager &pfm);              // Constructor
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
    RC DestroyIndex (const char *fileName,          // Destroy index
                     int        indexNo);
    /**
     * 打开一个索引文件，返回对应的idl(valid).
     * @param fileName
     * @param indexNo
     * @param indexHandle
     * @return
     */
    RC OpenIndex    (const char *fileName,          // Open index
                     int        indexNo,
                     IX_IndexHandle &indexHandle);
    RC CloseIndex   (IX_IndexHandle &indexHandle);  // Close index
private:
    FileManager &fileManager;
};

#endif //YOURSQL_IX_MANAGER_H

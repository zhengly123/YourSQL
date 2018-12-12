//
// Created by 杨乐 on 2018/12/10.
//

#ifndef YOURSQL_SM_MANAGER_H
#define YOURSQL_SM_MANAGER_H

#include <string>
#include "../IX/IX_PRIVATE.h"
#include "SM_PRIVATE.h"

struct AttrInfo {
    char     *attrName;           // Attribute name
    AttrType attrType;            // Type of attribute
    int      attrLength;          // Length of attribute
    int      offset;
    char     relName[MAXNAME+1];
};

// Used by Printer class
struct DataAttrInfo {
    char     relName[MAXNAME+1];  // Relation name
    char     attrName[MAXNAME+1]; // Attribute name
    int      offset;              // Offset of attribute
    AttrType attrType;            // Type of attribute
    int      attrLength;          // Length of attribute
    int      indexNo;             // Attribute index number
};

struct RelationMeta{
    char relName[MAXNAME];//	relation name
    int tupleLength;//	tuple length in bytes
    int attrCount;//	number of attributes
    int indexCount;//	number of indexed attributes
};


class SM_Manager {
public:
    SM_Manager  (IX_Manager &ixm, RM_Manager &rmm);  // Constructor
    ~SM_Manager ();                                  // Destructor
    RC createDb    (const char *dbName);
    RC OpenDb      (const char *dbName);                // Open database
    RC CloseDb     ();                                  // Close database
    RC CreateTable (const char *relName,                // Create relation
                    int        attrCount,
                    AttrInfo   *attributes);
    RC DropTable   (const char *relName);               // Destroy relation
    RC CreateIndex (const char *relName,                // Create index
                    const char *attrName);
    RC DropIndex   (const char *relName,                // Destroy index
                    const char *attrName);
    RC Load        (const char *relName,                // Load utility
                    const char *fileName);
    RC Help        ();                                  // Help for database
    RC Help        (const char *relName);               // Help for relation
    RC Print       (const char *relName);               // Print relation
    RC Set         (const char *paramName,              // Set system parameter
                    const char *value);

private:
    IX_Manager *ixm;
    RM_Manager *rmm;
    RM_FileHandle relcatHandler,attrcatHandler;
    bool isOpen;
    char initialCwd[2049];

    RC getRelFromCatelogy();
    //TODO: rel to file name should be down in file handler
    std::string relToFileName(const char *relName);
};

#endif //YOURSQL_SM_MANAGER_H

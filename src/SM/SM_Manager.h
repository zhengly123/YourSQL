//
// Created by 杨乐 on 2018/12/10.
//

#ifndef YOURSQL_SM_MANAGER_H
#define YOURSQL_SM_MANAGER_H

#include <string>
#include "SM_PRIVATE.h"
#include "../IX/IX_PRIVATE.h"
#include "../Printer/Printer.h"



class Printer;
// Used by Printer class
// 在redbase, this is used for test. It's trifling in our work.
struct DataAttrInfo {
    char     relName[MAXNAME+1];  // Relation name
    char     attrName[MAXNAME+1]; // Attribute name
    int      offset;              // Offset of attribute
    AttrType attrType;            // Type of attribute
    int      attrLength;          // Length of attribute
    int      indexNo;             // Attribute index number
};

struct RelationMeta{
    char relName[MAXNAME+1];//	relation name
    int tupleLength;//	tuple length in bytes
    int attrCount;//	number of attributes
    int indexCount;//	number of indexed attributes
};


class SM_Manager {
public:
    SM_Manager  (IX_Manager &ixm, RM_Manager &rmm);  // Constructor
    ~SM_Manager ();                                  // Destructor
    RC CreateDb(const char *dbName);
    RC OpenDb      (const char *dbName);                // Open database
    RC CloseDb     ();                                  // Close database
    RC DestroyDb(const char *dbName);                // Delete database
    RC CreateTable (const char *relName,                // Create relation
                    int        attrCount,
                    AttrInfo   *attributes);
    RC DropTable   (const char *relName);               // Destroy relation
    RC CreateIndex (const char *relName,                // Create index
                    const char *attrName);
    RC DropIndex   (const char *relName,                // Destroy index
                    const char *attrName);
    RC PrintTables ();
    RC Load        (const char *relName,                // Load utility
                    const char *fileName);
    RC Help        ();                                  // Help for database
    RC Help        (const char *relName);               // Help for relation
    RC Print       (const char *relName);               // Print relation
    RC Set         (const char *paramName,              // Set system parameter
                    const char *value);
    void flush();

    vector<RelationMeta> TestReturnTables();
    vector<AttrInfo> TestReturnAttrs();
private:
    IX_Manager *ixm;
    RM_Manager *rmm;
    RM_FileHandle relcatHandler,attrcatHandler;
    bool isOpen;
    std::string currentDbName;
    char initialCwd[2049];
    Printer *printer;

    RC getRelFromCatelogy();
    //TODO: rel to file name should be down in file handler
    std::string relToFileName(const char *relName)
    {
        return std::string(relName)+std::string(".rel");
    }
};

#endif //YOURSQL_SM_MANAGER_H

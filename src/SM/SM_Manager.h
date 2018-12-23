//
// Created by 杨乐 on 2018/12/10.
//

#ifndef YOURSQL_SM_MANAGER_H
#define YOURSQL_SM_MANAGER_H

#include "../IX/IX_PRIVATE.h"

class SM_Manager {
public:
    SM_Manager  (IX_Manager &ixm, RM_Manager &rmm);  // Constructor
    ~SM_Manager ();                                  // Destructor
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
};

#endif //YOURSQL_SM_MANAGER_H

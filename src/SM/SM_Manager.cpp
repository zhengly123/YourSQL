//
// Created by 杨乐 on 2018/12/10.
//

#include "SM_Manager.h"

SM_Manager :: SM_Manager(IX_Manager &ixm, RM_Manager &rmm)
{

}

SM_Manager :: ~SM_Manager ()
{

}

// Open database
RC SM_Manager :: OpenDb      (const char *dbName)
{
    cerr << "Opening DB : " << dbName << endl;
    return 0;
}

// Close database
RC SM_Manager :: CloseDb     ()
{

}

// Create relation
RC SM_Manager :: CreateTable (const char *relName, int attrCount, AttrInfo *attributes)
{
    std::cerr << "create table : " << relName << std::endl;
    for(int i = 0; i < attrCount; ++ i)
    {
        std::cerr << "  attr " << i << std::endl;
        std::cerr << "      attrName : " << attributes[i].attrName << std::endl;
        std::cerr << "      relName : " << attributes[i].relName << std::endl;
        std::cerr << "      attrType : " << attributes[i].attrType << std::endl;
        std::cerr << "      attrLength : " << attributes[i].attrLength << std::endl;
        std::cerr << "      flag : " << attributes[i].flag << std::endl;
    }
}

// Destroy relation
RC SM_Manager :: DropTable   (const char *relName)
{

}

// Create index
RC SM_Manager :: CreateIndex (const char *relName, const char *attrName)
{

}

// Destroy index
RC SM_Manager :: DropIndex   (const char *relName, const char *attrName)
{

}

// Load utility
RC SM_Manager :: Load        (const char *relName, const char *fileName)
{

}

// Help for database
RC SM_Manager :: Help        ()
{

}

// Help for relation
RC SM_Manager :: Help        (const char *relName)
{

}

// Print relation
RC SM_Manager :: Print       (const char *relName)
{

}

// Set system parameter
RC SM_Manager :: Set         (const char *paramName, const char *value)
{

}


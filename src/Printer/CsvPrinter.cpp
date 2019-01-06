//
// Created by 杨乐 on 2019/1/6.
//

#include "CsvPrinter.h"

CsvPrinter::~CsvPrinter()
{
    flush();
}

void CsvPrinter::flush()
{
    assert(false);
    //FILE* fp = fopen(fileName.c_str(), "w");
    //fprintf(fp, "%s", iss.str());
    //iss = stringstream();
}

void CsvPrinter::flush(std::string name)
{
    ofstream fout(name.c_str());
    fout << iss.str();
    iss = stringstream();
}

void CsvPrinter::syncFlush()
{
    if (sync)
        flush();
}

void CsvPrinter::setFile(std::string fileName)
{
    this->fileName = fileName;
}

void CsvPrinter::PrintValue(char *data, bool isNull, AttrType attrType)
{
    if(isNull == 1)
        iss << "NULL,";
    else if(attrType == INT)
        iss << *(int *) data<<",";
    else if(attrType == AttrType::FLOAT)
        iss << *(float *) data<<",";
    else if(attrType == STRING)
        iss << data <<",";
    else if(attrType == DATETYPE)
    {
        int dt = *(int*) data;
        iss << dt/10000 << "-" << dt%10000/100 << "-" << dt%100 << ",";
    }
    else
        iss << "***,";
}
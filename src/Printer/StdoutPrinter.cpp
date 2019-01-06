//
// Created by eric on 18-12-24.
//

#include "StdoutPrinter.h"

StdoutPrinter::~StdoutPrinter()
{
    flush();
}

void StdoutPrinter::flush()
{
    cout << iss.str();
    iss = stringstream();
}

void StdoutPrinter::syncFlush()
{
    if (sync)
        flush();
}

void StdoutPrinter::flush(std::string name)
{
    assert(false);
}

void StdoutPrinter::PrintValue(char *data, bool isNull, AttrType attrType)
{
    if(isNull == 1)
        iss << "      NULL      ";
    else if(attrType == INT)
        iss << *(int *) data<<" ";
    else if(attrType == AttrType::FLOAT)
        iss << *(float *) data<<" ";
    else if(attrType == STRING)
        iss << data <<" ";
    else if(attrType == DATETYPE)
    {
        int dt = *(int*) data;
        iss << dt/10000 << "-" << dt%10000/100 << "-" << dt%100 << " ";
    }
    else
        iss << "       ***      ";
}
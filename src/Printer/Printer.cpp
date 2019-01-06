//
// Created by eric on 18-12-24.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include "Printer.h"
using namespace std;
int AttrOutputWidth[]={10,10,10,0,0,0};

Printer::Printer(bool sync) : sync(sync), attrCount(0), attrInfo(nullptr)
{
}

Printer::~Printer()
{
    if (attrInfo)
        delete[] attrInfo;
}

void Printer::setAttr(const DataAttrInfo *attributes, const int attrCount)
{
    if (attrInfo)
        delete[] attrInfo;
    attrInfo = new DataAttrInfo[attrCount];
    memcpy(attrInfo, attributes, sizeof(DataAttrInfo) * attrCount);
    width = 0;
    outputWidth.clear();
}

void Printer::PrintHeader()
{
    int  curWidth, valueWidth;
    for (int i=0;i<attrCount;++i)
    {
        curWidth=max(AttrOutputWidth[attrInfo[i].attrLength],
                     (int)(strlen(attrInfo[i].attrName)+strlen(attrInfo[i].relName)));
        width+=curWidth;
        outputWidth.push_back(curWidth);
//        if (attrInfo[i].attrType!=AttrType::STRING)
        outputString(string(attrInfo[i].relName) + string(":") + attrInfo[i].attrName,
                     curWidth);
//            iss << string(attrInfo[i].relName) << ':' << attrInfo[i].attrName;
//        else
//            iss<<setw()
    }
    iss << endl;
    syncFlush();
}

void Printer::outputString(string s, int len)
{
    if (s.length() <= len)
    {
        iss << setw(len) << s;
    } else
    {
        iss << s.substr(0, len);
    }
}

void Printer::Print(const char * const data)
{
    for (int i = 0; i < attrCount; ++i)
    {
        iss << setw(outputWidth[i]);
        if (attrInfo[i].attrType==AttrType::STRING)
        {
            string s = string((char *) data + attrInfo[i].offset);
            s = s.substr(0, outputWidth[i]);
            outputString(s, outputWidth[i]);
        } else if (attrInfo[i].attrType == AttrType::INT)
        {
            iss << *(int *) (data + attrInfo[i].offset);
        } else if (attrInfo[i].attrType == AttrType::FLOAT)
        {
            iss << *(float *) (data + attrInfo[i].offset);
        } else {
            iss << "";
        }
    }
    iss << endl;
    syncFlush();
}

void Printer::Print(const char *const data[], int tupleCnt)
{
    for (int i=0;i<tupleCnt;++i)
    {
        Print(data[i]);
    }
    printCnt = tupleCnt;
}

void Printer::PrintFooter()
{
    for (int i = 0; i < width; ++i)
        iss<<'-';
    iss << endl;
    iss << "#Output tuples=" << attrCount << endl;
    for (int i = 0; i < width; ++i)
        iss<<'=';
    iss << endl;
    attrCount = 0;
    syncFlush();
}

void Printer::syncFlush()
{

}

void Printer::PrintTablesInfo(const RelationMeta *data, int tupleCnt)
{
    for (int i = 0; i < tupleCnt; ++i)
    {
        iss << setw(10) << data[i].relName << setw(10)
            << data[i].attrCount << setw(10) << data[i].indexCount << endl;
    }
}


void Printer::Println()
{
    iss << "\n";
}

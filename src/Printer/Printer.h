//
// Created by eric on 18-12-24.
//

#ifndef YOURSQL_PRINTER_H
#define YOURSQL_PRINTER_H
#include <string>
#include <iostream>
#include <sstream>
#include "../SM/SM_Manager.h"

using namespace std;

struct DataAttrInfo;
struct RelationMeta;

class Printer
{
public:
    Printer(bool sync = true);
    ~Printer();
    void setAttr(const DataAttrInfo *attributes, const int attrCount);
    void PrintHeader();
    void Print(const char * const data);

    void Print(const char *const data[], int tupleCnt);
    void PrintTablesInfo(const RelationMeta *data, int tupleCnt);
    void PrintValue(char *data, bool isNull, AttrType attrType);
    void Println();
    void PrintFooter();
//    void PrintTable(vector<AttrInfo> attrs,);

//    template <typename T>
//    Printer& operator <<(const T b);
//    Printer& operator <<(T b);
    stringstream& getSS(){
        return iss;
    }

    virtual void flush() = 0;
    virtual void syncFlush();

protected:
    stringstream iss;
    bool sync;

private:
//    int buffersize;
    string buf;

    DataAttrInfo *attrInfo;
    int attrCount, width;
    vector<int> outputWidth;

//    bool overflow;
    int printCnt;

    void outputString(string s, int len);
};


#endif //YOURSQL_PRINTER_H

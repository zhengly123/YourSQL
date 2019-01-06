//
// Created by 杨乐 on 2019/1/6.
//

#ifndef YOURSQL_CSVPRINTER_H
#define YOURSQL_CSVPRINTER_H


#include "Printer.h"

class CsvPrinter: public Printer
{
public:
    ~CsvPrinter();
    void flush() override;
    void syncFlush() override;
    void flush(std::string name) override;
    void PrintValue(char *data, bool isNull, AttrType attrType) override;
    void setFile(std::string fileName);
private:
    std::string fileName;
};


#endif //YOURSQL_CSVPRINTER_H

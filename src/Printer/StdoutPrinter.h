//
// Created by eric on 18-12-24.
//

#ifndef YOURSQL_STDOUTPRINTER_H
#define YOURSQL_STDOUTPRINTER_H

#include "Printer.h"

class StdoutPrinter: public Printer
{
public:
    ~StdoutPrinter();
    void flush() override;
    void syncFlush() override;
    void flush(std::string name) override;
    void PrintValue(char *data, bool isNull, AttrType attrType) override;
};


#endif //YOURSQL_STDOUTPRINTER_H

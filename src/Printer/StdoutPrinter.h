//
// Created by eric on 18-12-24.
//

#ifndef YOURSQL_STDOUTPRINTER_H
#define YOURSQL_STDOUTPRINTER_H

#include "Printer.h"

class StdoutPrinter: public Printer
{
    ~StdoutPrinter();
    void flush() override;
    void syncFlush() override;
};


#endif //YOURSQL_STDOUTPRINTER_H

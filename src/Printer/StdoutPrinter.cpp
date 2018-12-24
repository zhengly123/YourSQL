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

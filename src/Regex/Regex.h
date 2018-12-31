//
// Created by eric on 18-12-31.
//

#ifndef YOURSQL_REGEX_H
#define YOURSQL_REGEX_H

#include <cstring>
#include <string>
#include <vector>
using namespace std;

class Regex
{
public:
    const char ANY='%';
    const char ONE='_';
//    struct Seperator
//    {
//        int pos;
//    };
    Regex(const char *p);

    bool checkLegalRegex(const char *cp);

    bool match(const char *ca);

    bool isDead(){ return dead; }
private:

    vector<int> sep;
    string p;
    bool dead;
};


#endif //YOURSQL_REGEX_H

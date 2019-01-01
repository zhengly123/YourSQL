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
    // 合法的特殊符号为%(至少一个字符),_(匹配一个字符),[](一个集合中的字符),
    // [^](一个集合外的字符)
    const char ANY='%';
    const char ONE='_';
    /**
     * Construct a regex with pattern. After construction, use isDead to
     * check whether the pattern is legal.
     * @param p Pattern string
     */
    Regex(const char *p);


    /**
     * Match a string.
     * @param ca
     * @return If match, return true. Otherwise return false.
     */
    bool match(const char *ca);

    /**
     * If is legal, return false.
     * @return
     */
    bool isDead(){ return dead; }
private:
    bool checkLegalRegex(const char *cp);

    vector<int> sep;
    string p;
    bool dead;
};


#endif //YOURSQL_REGEX_H

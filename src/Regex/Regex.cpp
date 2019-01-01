//
// Created by eric on 18-12-31.
//

#include "Regex.h"

Regex::Regex(const char *p)
{
    dead = !checkLegalRegex(p);
}

bool Regex::checkLegalRegex(const char *cp)
{
    p = cp;
    bool inSelect = false;
    sep.push_back(-1);
    for (int i = 0; i < p.length(); ++i)
    {
        if (p[i] == '[')
        {
            if (inSelect)
                return false;
            sep.push_back(i);
            inSelect = true;
        } else if (p[i] == ']')
        {
            if (!inSelect)
                return false;
            inSelect = false;
        } else if (inSelect)
        {
            if (p[i] == ANY || p[i] == ONE)
            {
                return false;
            } else if (p[i] == '^')
            {
                if (sep.back() != i - 1)
                    return false;
            }
        } else
            sep.push_back(i);
    }
    return !inSelect;
}

bool Regex::match(const char *ca)
{
    string a = string(" ") + ca;
    std::vector<std::vector<bool>> f(a.size(),
                                     vector<bool>(sep.size(), false));

    f[0][0] = true;
    for (int i = 1; i < a.length(); ++i)
    {
        for (int j = 1; j < sep.size(); ++j)
        {
            if (f[i - 1][j - 1])
            {
                if ((a[i] == p[sep[j]] || p[sep[j]] == ANY|| p[sep[j]] == ONE))
                    f[i][j] = true;
                else if (p[sep[j]] == '[')
                {
                    if (p[sep[j] + 1] == '^')
                    {
                        f[i][j] = true;
                        for (int k = sep[j]+2; p[k] != ']'; ++k)
                        {
                            if (p[k]==a[i])
                            {
                                f[i][j]=false;
                                break;
                            }
                        }
                    } else
                    {
                        f[i][j] = false;
                        for (int k = sep[j]+1; p[k] != ']'; ++k)
                        {
                            if (p[k]==a[i])
                            {
                                f[i][j] = true;
                                break;
                            }
                        }
                    }
                }
            } else if (f[i - 1][j] && p[sep[j]] == ANY)
            {
                f[i][j] = true;
            }
        }
    }
    return f[a.size() - 1][sep.size() - 1];
}


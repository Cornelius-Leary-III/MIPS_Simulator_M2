#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <map>
#include <string>

using std::map;
using std::pair;
using std::make_pair;
using std::string;

class Constants
{
public:
    Constants();

    bool addConstant(const string& constantName, int constantValue);
    map<string, int>::iterator lookupConstant(const string& constantName);
    void setConstants(const map<string, int>& newConstants);
    map<string, int>& getConstants();

private:

    map<string, int> constants;
};

#endif // CONSTANTS_H

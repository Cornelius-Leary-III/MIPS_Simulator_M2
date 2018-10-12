#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <map>
#include <vector>
#include <string>

using std::map;
using std::pair;
using std::make_pair;
using std::vector;
using std::string;

class Constants
{
public:
    Constants();
    Constants(const vector<string>& nameVector,
              const vector<int>& valueVector);

    bool addConstant(const string& constantName, int constantValue);
    map<string, int>::iterator lookupConstant(const string& constantName);
    void setConstants(const map<string, int>& newConstants);
    map<string, int>& getConstants();

private:

    map<string, int> constants;
    map<string, int>::iterator constantsEnd;
};

#endif // CONSTANTS_H

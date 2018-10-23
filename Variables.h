#ifndef VARIABLES_H
#define VARIABLES_H

#include <map>
#include <string>

using std::map;
using std::pair;
using std::make_pair;
using std::string;

struct variableData
{
    unsigned memoryIndex;
    unsigned variableSizeInBytes;
    string initialValue;
    string currentValue;
};

class Variables
{
public:
    Variables();

    bool addVariable(const string& newVariableName,
                     unsigned newVariableSizeInBytes,
                     string newVariableValue);

    map<string, variableData>::iterator lookupVariable(const string& variableName);
    bool updateVariableValue(const string& variableName, const string& newValue);
    void setVariables(const map<string, variableData>& newVariables);
    map<string, variableData>& getVariables();

private:
    map<string, variableData> variables;
    map<string, variableData>::iterator variablesEnd;
    unsigned nextAvailableAddress;
};

#endif // VARIABLES_H

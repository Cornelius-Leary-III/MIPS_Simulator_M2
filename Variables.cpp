#include "Variables.h"

Variables::Variables()
{
    variables;
    variablesEnd = variables.end();
    nextAvailableAddress = 0;
}

bool Variables::addVariable(const string& newVariableName,
                            unsigned newVariableSizeInBytes,
                            string newVariableValue)
{
    variableData newVariable;
    newVariable.memoryIndex = nextAvailableAddress;
    newVariable.variableSizeInBytes = newVariableSizeInBytes;
    newVariable.initialValue = newVariableValue;
    newVariable.currentValue = newVariableValue;

    auto insertIter = variables.insert(make_pair(newVariableName, newVariable));

    nextAvailableAddress += newVariableSizeInBytes;

    return insertIter.second;
}

map<string, variableData>::iterator Variables::lookupVariable(const string& variableName)
{
    auto lookupIter = variables.find(variableName);
    if (lookupIter != variablesEnd)
    {
        return lookupIter;
    }

    return variablesEnd;
}

void Variables::setVariables(const map<string, variableData>& newVariables)
{
    variables = newVariables;
}

map<string, variableData>& Variables::getVariables()
{
    return variables;
}


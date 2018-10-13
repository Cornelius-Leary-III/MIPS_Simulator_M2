#ifndef VARIABLESANDMEMORYHANDLER_H
#define VARIABLESANDMEMORYHANDLER_H

#include "Memory.h"
#include "Variables.h"

class VariablesAndMemoryHandler
{
public:
    VariablesAndMemoryHandler();

    void setMemory(const Memory& newMemory);
    void setVariables(const Variables& newVariables);

    Memory& getMemory();
    Variables& getVariables();
    bool processVariable(const string& variableName,
                         const string& variableValue,
                         unsigned variableSizeInBytes);

private:

    Memory memory;
    Variables variables;

};

#endif // VARIABLESANDMEMORYHANDLER_H

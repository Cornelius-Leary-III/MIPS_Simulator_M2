#ifndef VMCONTENTS_H
#define VMCONTENTS_H

#include "Constants.h"
#include "Labels.h"
#include "Variables.h"
#include "Memory.h"
#include "RawInstruction.h"
#include "Registers.h"

struct VMContents
{
    Constants* constantsPtr;
    Labels* labelsPtr;
    Memory* memoryPtr;
    Variables* variablesPtr;
    vector<RawInstruction>* programPtr;
    map<string, string>* validRegisterNamesMapPtr;
    Registers* registersPtr;
};

#endif // VMCONTENTS_H

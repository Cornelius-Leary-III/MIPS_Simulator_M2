#ifndef VMCONTENTS_H
#define VMCONTENTS_H

#include "Constants.h"
#include "Labels.h"
#include "Variables.h"
#include "Memory.h"
#include "Instruction.h"

struct VMContents
{
    Constants* constantsPtr;
    Labels* labelsPtr;
    Memory* memoryPtr;
    Variables* variablesPtr;
    vector<Instruction>* programPtr;
};

#endif // VMCONTENTS_H

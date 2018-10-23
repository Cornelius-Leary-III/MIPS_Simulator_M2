#ifndef VMCONTENTS_H
#define VMCONTENTS_H

#include "Constants.h"
#include "Labels.h"
#include "Registers.h"
#include "VariablesAndMemoryHandler.h"

struct VMContents
{
    Constants* constantsPtr;
    Labels* labelsPtr;
    Memory* memoryPtr;
    Variables* variablesPtr;
};

#endif // VMCONTENTS_H

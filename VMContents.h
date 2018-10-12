#ifndef VMCONTENTS_H
#define VMCONTENTS_H

#include "Constants.h"
#include "Labels.h"
#include "Memory.h"
#include "Registers.h"

//class VMContents
//{
//public:

//    VMContents();

//    Constants& getConstants();
//    Labels& getLabels();
//    Memory& getMemory();
//    Registers& getRegisters();

//private:

//    Constants vm_constants;
//    Labels vm_labels;
//    Memory vm_memory;
//    Registers vm_registers;
//};

struct VMContents
{
    Constants vmConstants;
    Labels vmLabels;
    Memory vmMemory;
    Registers vmRegisters;
};

#endif // VMCONTENTS_H

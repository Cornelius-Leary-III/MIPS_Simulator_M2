#ifndef VMCONTENTS_H
#define VMCONTENTS_H

#include "Constants.h"
#include "Labels.h"
#include "Registers.h"
#include "VariablesAndMemoryHandler.h"

//class VMContents
//{
//public:

//    VMContents();

//    Constants& getConstants();
//    Labels& getLabels();
////    Registers& getRegisters();

//    void setConstants(const Constants& newConstants);
//    void setLabels(const Labels& newLabels);
////    void setRegisters(const Registers& newRegisters);

//private:

//    Constants vmConstants;
//    Labels vmLabels;
////    Registers vmRegisters;
//    VariablesAndMemoryHandler varMemHandler;
//};

struct VMContents
{
    Constants* constantsPtr;
    Labels* labelsPtr;
    Memory* memoryPtr;
    Variables* variablesPtr;

//    VariablesAndMemoryHandler* varMemHandlerPtr;
//    Registers* registersPtr;
};

#endif // VMCONTENTS_H

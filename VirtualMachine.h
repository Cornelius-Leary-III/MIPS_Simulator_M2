#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "lexer.h"
#include "parser.h"
#include "VMContents.h"
#include "InstructionProcessor.h"
#include "MIPS_Simulator.h"

class VirtualMachine
{
public:
    VirtualMachine();

private:

    parser parser_mipsI;
    InstructionProcessor instructionHandler;
    MIPS_Simulator* simulator_mipsI;

    VMContents* contents;


};

#endif // VIRTUALMACHINE_H

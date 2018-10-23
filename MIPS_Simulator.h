#ifndef MIPS_SIMULATOR_H
#define MIPS_SIMULATOR_H

#include "parser.h"


class MIPS_Simulator
{
public:
    MIPS_Simulator();

    //TODO: determine how to turn the simulator interface section, described in the Milestone, into
    //          particular methods.

    //TODO: these are the likely methods:
    //          * parse file
    //          * print register contents (for particular register)
    //          * print memory contents (for particular address)
    //          * execute current instruction
    //          * print error status
    //          * quit successfully
    //          * quit due to failure

private:

    parser mipsParser;

    int currentInstruction;

    // TODO: determine the minimum necessary members to properly meet requirements,
    //          while avoiding all circular dependencies and excessive time / space complexity.

};

#endif // MIPS_SIMULATOR_H

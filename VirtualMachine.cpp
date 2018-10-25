#include "VirtualMachine.h"

VirtualMachine::VirtualMachine()
{
    contents = new VMContents();

    // TODO: initialize contents member.

    parser_mipsI;
    instructionHandler;
    simulator_mipsI = new MIPS_Simulator(contents);
}

// TODO: determine structure that doesn't create any dependency loops!

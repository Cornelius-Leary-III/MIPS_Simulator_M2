#ifndef INSTRUCTIONPROCESSOR_H
#define INSTRUCTIONPROCESSOR_H

#include "VMContents.h"
#include "Instructions.h"


class InstructionProcessor
{
public:
    InstructionProcessor();
    ~InstructionProcessor();

    void setVMContents(VMContents* newVMContentsPtr);
    bool processRawInstructions();

    vector<InstructionBase*>& getProgram();

private:

    VMContents* vmContentsPtr;
    vector<InstructionBase*> processedInstructions;
};

#endif // INSTRUCTIONPROCESSOR_H

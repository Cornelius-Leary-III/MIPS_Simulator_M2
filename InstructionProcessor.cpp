#include "InstructionProcessor.h"

InstructionProcessor::InstructionProcessor()
{
    vmContentsPtr = nullptr;
    processedInstructions;
}

InstructionProcessor::~InstructionProcessor()
{
    if (vmContentsPtr)
    {
        delete vmContentsPtr;
        vmContentsPtr = nullptr;
    }
}

void InstructionProcessor::setVMContents(VMContents* newVMContentsPtr)
{
    vmContentsPtr = newVMContentsPtr;
}

bool InstructionProcessor::processRawInstructions()
{
    auto rawInstructionSet = vmContentsPtr->programPtr;

//    auto instructionCount = rawInstructionSet->size();
    auto instructionIter = rawInstructionSet->begin();
    auto instructionsEnd = rawInstructionSet->end();

    while (instructionIter != instructionsEnd)
    {
        string currentOperation = instructionIter->getOperation();
        vector<string> currentArguments = instructionIter->getArguments();

        if (currentOperation == "lw")
        {
            // LoadWord
        }
        else if (currentOperation == "lh")
        {
            // LoadHalf
        }
        else if (currentOperation == "lb")
        {
            // LoadByte
        }
        else if (currentOperation == "li")
        {
            // LoadImmediate
        }
        else if (currentOperation == "la")
        {
            // LoadAddress
        }
        else if (currentOperation == "sw")
        {
            // StoreWord
        }
        else if (currentOperation == "sh")
        {
            // StoreHalf
        }
        else if (currentOperation == "sb")
        {
            // StoreByte
        }
        else if (currentOperation == "move")
        {
            // Move
        }
        else if (currentOperation == "mfhi")
        {
            // MoveFromHigh
        }
        else if (currentOperation == "mflo")
        {
            // MoveFromLow
        }
        else if (currentOperation == "mthi")
        {
            // MoveToHigh
        }
        else if (currentOperation == "mtlo")
        {
            // MoveToLow
        }
        else if (currentOperation == "add")
        {
            // Add
        }
        else if (currentOperation == "addu")
        {
            // AddUnsigned
        }
        else if (currentOperation == "sub")
        {
            // Subtract
        }
        else if (currentOperation == "subu")
        {
            // SubtractUnsigned
        }
        else if (currentOperation == "mul")
        {
            // Multiply32
        }
        else if (currentOperation == "mulo")
        {
            // Multiply32WithOverflow
        }
        else if (currentOperation == "mulou")
        {
            // Multiply32WithOverflowUnsigned
        }
        else if (currentOperation == "mult")
        {
            // Multiply64Signed
        }
        else if (currentOperation == "multu")
        {
            // Multiply64Unsigned
        }
        else if (currentOperation == "div")
        {
            // DivideSigned
            // DivideSignedWithRemainder
        }
        else if (currentOperation == "divu")
        {
            // DivideUnsigned
            // DivideUnsignedWithRemainder
        }
        else if (currentOperation == "rem")
        {
            // RemainderSigned
        }
        else if (currentOperation == "remu")
        {
            // RemainderUnsigned
        }
        else if (currentOperation == "abs")
        {
            // AbsoluteValue
        }
        else if (currentOperation == "neg")
        {
            // NegateSigned
        }
        else if (currentOperation == "negu")
        {
            // NegateUnsigned
        }
        else if (currentOperation == "and")
        {
            // AndLogical
        }
        else if (currentOperation == "nor")
        {
            // NorLogical
        }
        else if (currentOperation == "not")
        {
            // NotLogical
        }
        else if (currentOperation == "or")
        {
            // OrLogical
        }
        else if (currentOperation == "xor")
        {
            // XorLogical
        }
        else if (currentOperation == "j")
        {
            // Jump
        }
        else if (currentOperation == "beq")
        {
            // BranchEqual
        }
        else if (currentOperation == "bne")
        {
            // BranchNotEqual
        }
        else if (currentOperation == "blt")
        {
            // BranchLessThan
        }
        else if (currentOperation == "ble")
        {
            // BranchLessThanOrEqual
        }
        else if (currentOperation == "bgt")
        {
            // BranchGreaterThan
        }
        else if (currentOperation == "bge")
        {
            // BranchGreaterThan
        }
        else if (currentOperation == "nop")
        {
            // NoOperation
        }

        ++instructionIter;
    }


    return true;
}

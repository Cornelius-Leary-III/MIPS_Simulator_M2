#include "Instructions.h"

InstructionBase::InstructionBase()
{
    vmContentsPtr = new VMContents();
    vmContentsPtr->constantsPtr = new Constants();
    vmContentsPtr->labelsPtr = new Labels();
    vmContentsPtr->memoryPtr = new Memory();
    vmContentsPtr->variablesPtr = new Variables();
    vmContentsPtr->programPtr = new vector<RawInstruction>();
}

void InstructionBase::execute()
{
    cout << "base instruction carried out" << endl;
}

VMContents* InstructionBase::getContents()
{
    return vmContentsPtr;
}

void InstructionBase::setContents(VMContents* newContents)
{
    vmContentsPtr = newContents;
}

//LoadWord::LoadWord()
//    : InstructionBase()
//{

//}

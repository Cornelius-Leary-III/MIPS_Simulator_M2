#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "VMContents.h"

#include <iostream>
using std::cout;
using std::endl;

class InstructionBase
{
public:
    InstructionBase();
//    virtual ~InstructionBase() = 0; //TODO: determine rules of destructors in classes derived from base class and for the base class.
    virtual void execute(VMContents* newContents);
    virtual void setContents(VMContents* newContents);
    virtual VMContents* getContents();

protected:
    VMContents* vmContentsPtr;
};

//class LoadWord : public InstructionBase
//{
//public:

//    LoadWord();
//    void execute();

//protected:

//};

//class

#endif // INSTRUCTIONS_H

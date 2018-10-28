#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "lexer.h"
#include "parser.h"
#include "VMContents.h"
#include "InstructionProcessor.h"
#include "MIPS_Simulator.h"

#include "Program.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class VirtualMachine
{
public:

    VirtualMachine();
    ~VirtualMachine();

    int userIOLoop(const string& fileToProcess);

private:

    bool setup(const string& inputFile);
    bool tokenizeFile(const string& fileToTokenize);
    bool parseTokens();
    bool processInstructions();

    bool checkForErrors();

    string& getErrorMessage();
    string printRegisterContents(const string& registerName);
    string printByteFromMemory(unsigned memoryAddress);
    void executeCurrentStep();

    lexer fileLexer;
    parser fileParser;
    InstructionProcessor instructionHandler;
    int currentInstruction;
    vector<InstructionBase*> program;
    VMContents* contents;

    bool errorFlag;
    string errorMessage;
    bool tokenizedSuccessfully;
    bool parsedSuccessfully;
    bool instructionsProcessedSuccessfully;

};

#endif // VIRTUALMACHINE_H

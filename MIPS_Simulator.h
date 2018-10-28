//#ifndef MIPS_SIMULATOR_H
//#define MIPS_SIMULATOR_H

//#include "parser.h"
//#include "Instructions.h"

//#include <fstream>
//using std::ifstream;

//class MIPS_Simulator
//{
//public:
//    MIPS_Simulator(VMContents* contentsPtr);

//    //TODO: determine how to turn the simulator interface section, described in the Milestone, into
//    //          particular methods.

////    bool parseFile(const string& fileToParse);
////    bool parseStream(std::istream& streamToParse);
////    bool processRawInstructions();
//    bool printRegisterContents(const string& registerName);
//    bool printByteInMemory(unsigned byteAddress);
//    bool executeCurrentInstruction();

//    int processUserInputLoop();

//    //TODO: these are the likely methods:
//    //          * parse file
//    //          * print register contents (for particular register)
//    //          * print memory contents (for particular address)
//    //          * execute current instruction
//    //          * print error status
//    //          * quit successfully
//    //          * quit due to failure

//private:

////    parser mipsParser;
////    string fileToParse;
//    int currentInstruction;
//    vector<InstructionBase*> program;
//    VMContents* contentsPtr;

//    // TODO: determine the minimum necessary members to properly meet requirements,
//    //          while avoiding all circular dependencies and excessive time / space complexity.

//};

//#endif // MIPS_SIMULATOR_H

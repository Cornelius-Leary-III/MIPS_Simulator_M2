#ifndef INSTRUCTIONPARSER_H
#define INSTRUCTIONPARSER_H

#include "token.h"

#include "VMContents.h"

#include <sstream>
using std::stringstream;

#include <string>
using std::string;

class InstructionParser
{
public:
    InstructionParser(const tokenVector& currentLineToParse,
                      VMContents* newContentsPtr);

    bool parse_Instruction();
    bool parse_LabelForInstruction();
    bool parse_Operation();
    bool parse_Register();
    bool parse_MemoryReference();
    bool parse_Source();
    bool parse_Immediate();
    bool parse_Immediate_Digits();
    bool parse_Immediate_Constant();
    bool parse_Variable();

    bool parse_DataMovementInstruction();
    bool parse_DMI_2_args();
    bool parse_DMI_2_args_load();
    bool parse_DMI_2_args_store();
    bool parse_DMI_move();

    bool parse_IntegerArithmeticInstruction();
    bool parse_IAI_2_args();
    bool parse_IAI_3_args();
    bool parse_IAI_div();

    bool parse_LogicalInstruction();
    bool parse_LI_3_args();
    bool parse_LI_not();

    bool parse_ControlInstruction();
    bool parse_CI_jump();
    bool parse_CI_3_args();

    bool parse_Digit(char currentChar);
    bool parse_Alpha(char currentChar);
    bool parse_Char(char currentChar);

private:

    void addRawInstructionToSet();
    bool checkForValidRegisterName(const string& registerName);
    bool checkForValidRegisterNumber(const string& registerNumber);
    bool checkForValidRegisterAlias(const string& registerAlias);

    tokenVector lineOfTokens;
    tokenVector::iterator currentToken;
    tokenVector::iterator lineEnd;
    VMContents* contentsPtr;

    string currentInstructionName;
    vector<string> currentInstructionArguments;

};

#endif // INSTRUCTIONPARSER_H

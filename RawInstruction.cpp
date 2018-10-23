#include "RawInstruction.h"

RawInstruction::RawInstruction()
{
    operation = "nop";
    arguments;
    lineNumber = 1;
}

string& RawInstruction::getOperation()
{
    return operation;
}

vector<string>& RawInstruction::getArguments()
{
    return arguments;
}

void RawInstruction::setOperation(const string& newOperation)
{
    operation = newOperation;
}

void RawInstruction::setArguments(const vector<string>& newArguments)
{
    arguments = newArguments;
}

void RawInstruction::appendArgument(const string& argumentToAppend)
{
    arguments.push_back(argumentToAppend);
}

void RawInstruction::setLine(unsigned newLineNumber)
{
    lineNumber = newLineNumber;
}

#include "Instruction.h"

Instruction::Instruction()
{
    operation = "nop";
    arguments;
}

string& Instruction::getOperation()
{
    return operation;
}

vector<string>& Instruction::getArguments()
{
    return arguments;
}

void Instruction::setOperation(const string& newOperation)
{
    operation = newOperation;
}

void Instruction::setArguments(const vector<string>& newArguments)
{
    arguments = newArguments;
}

void Instruction::appendArgument(const string& argumentToAppend)
{
    arguments.push_back(argumentToAppend);
}


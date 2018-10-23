#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class Instruction
{
public:
    Instruction();

    string& getOperation();
    vector<string>& getArguments();

    void setOperation(const string& newOperation);
    void setArguments(const vector<string>& newArguments);
    void appendArgument(const string& argumentToAppend);

private:
    string operation;
    vector<string> arguments;
};

#endif // INSTRUCTION_H

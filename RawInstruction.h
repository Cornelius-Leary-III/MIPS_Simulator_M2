#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class RawInstruction
{
public:
    RawInstruction();

    string& getOperation();
    vector<string>& getArguments();

    void setOperation(const string& newOperation);
    void setArguments(const vector<string>& newArguments);
    void appendArgument(const string& argumentToAppend);
    void setLine(unsigned newLineNumber);

private:
    string operation;
    vector<string> arguments;
    unsigned lineNumber;
};

#endif // INSTRUCTION_H

#ifndef REGISTERS_H
#define REGISTERS_H

#include <map>
#include <string>

using std::map;
using std::pair;
using std::make_pair;
using std::string;

class Registers
{
public:
    Registers();

    bool addRegister(const string& registerName, int registerValue);
    bool updateRegister(const string& registerName, int registerValue);
    map<string, int>::iterator moveRegisterContents(const string& destination,
                                                    const string& source);
    map<string, int>::iterator lookupRegister(const string& registerName);
    void setRegisters(const map<string, int>& newRegisters);
    map<string, int>& getRegisters();

private:

    map<string, int> registers;
};

#endif // REGISTERS_H

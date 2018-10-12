#include "Registers.h"

//TODO: implement appropriate constructor(s).
Registers::Registers()
{
    registers;
    registersEnd = registers.end();
}

bool Registers::addRegister(const string& registerName, int registerValue)
{
    auto insertIter = registers.insert(make_pair(registerName, registerValue));
    return insertIter.second;
}

bool Registers::updateRegister(const string& registerName, int registerValue)
{
    auto updateIter = registers.find(registerName);
    if (updateIter != registersEnd)
    {
        updateIter->second = registerValue;
        return true;
    }
    else
    {
        auto insertIter = registers.insert(make_pair(registerName, registerValue));
        return insertIter.second;
    }
}

map<string, int>::iterator Registers::moveRegisterContents(const string& destination,
                                                           const string& source)
{
    auto sourceIter = lookupRegister(source);
    if (sourceIter != registersEnd)
    {
        if (updateRegister(destination, sourceIter->second))
        {
            updateRegister(source, 0);
            return registers.find(destination);
        }
    }

    return registersEnd;
}

map<string, int>::iterator Registers::lookupRegister(const string& registerName)
{
    auto lookupIter = registers.find(registerName);
    if (lookupIter != registersEnd)
    {
        return lookupIter;
    }

    return registersEnd;
}

void Registers::setRegisters(const map<string, int>& newRegisters)
{
    registers = newRegisters;
}

map<string, int>& Registers::getRegisters()
{
    return registers;
}

#include "Registers.h"

//TODO: implement appropriate constructor(s).
Registers::Registers()
{

}

//TODO: implement method to add register to map.
bool Registers::addRegister(const string& registerName, int registerValue)
{
    return true;
}

//TODO: implement method to update register with new value.
bool Registers::updateRegister(const string& registerName, int registerValue)
{
    return true;
}

//TODO: implement method to move contents of one register to another register.
map<string, int>::iterator Registers::moveRegisterContents(const string& destination,
                                                           const string& source)
{
    return registers.begin();
}

//TODO: implement method to lookup a specific register.
map<string, int>::iterator Registers::lookupRegister(const string& registerName)
{
    return registers.begin();
}

//TODO: implement method to set registers with new map of registers.
void Registers::setRegisters(const map<string, int>& newRegisters)
{
    return;
}

map<string, int>& Registers::getRegisters()
{
    return registers;
}

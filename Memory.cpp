#include "Memory.h"

//TODO: implement appropriate constructor(s).
Memory::Memory()
{

}

//TODO: implement method to add byte to memory.
bool Memory::addByteToMemory(uint8_t newByte)
{
    return true;
}

//TODO: implement method to update byte at specific memory location.
bool Memory::updateMemory(unsigned byteIndex, uint8_t newByte)
{
    return true;
}

unsigned long Memory::getMemorySize() const
{
    return memory.size();
}

//TODO: implement method to get specific byte from memory.
uint8_t Memory::getByteFromMemory(unsigned byteIndex)
{
    return '0';
}

//TODO: implement method to set memory with new vector of bytes.
void Memory::setMemory(const vector<uint8_t>& newMemory)
{
    return;
}

vector<uint8_t>& Memory::getMemory()
{
    return memory;
}

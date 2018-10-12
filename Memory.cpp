#include "Memory.h"

Memory::Memory()
{
    memory;
    memoryMaxSize = 512;
}

bool Memory::addByteToMemory(uint8_t newByte)
{
    if (memory.size() < memoryMaxSize)
    {
        memory.push_back(newByte);
        return true;
    }

    return false;
}

bool Memory::updateMemory(unsigned byteIndex, uint8_t newByte)
{
    if (byteIndex < memory.size())
    {
        memory[byteIndex] = newByte;
        return true;
    }

    return false;
}

unsigned long Memory::getMemorySize() const
{
    return memory.size();
}

uint8_t Memory::getByteFromMemory(unsigned byteIndex)
{
    if (byteIndex < memory.size())
    {
        return memory[byteIndex];
    }

    return '*';
}

void Memory::setMemory(const vector<uint8_t>& newMemory)
{
    memory = newMemory;
}

vector<uint8_t>& Memory::getMemory()
{
    return memory;
}

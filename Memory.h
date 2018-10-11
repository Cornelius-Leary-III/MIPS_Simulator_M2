#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <iostream>

using std::vector;

class Memory
{
public:
    Memory();

    bool addByteToMemory(uint8_t newByte);
    bool updateMemory(unsigned byteIndex, uint8_t newByte);
    unsigned long getMemorySize() const;
    uint8_t getByteFromMemory(unsigned byteIndex);
    void setMemory(const vector<uint8_t>& newMemory);
    vector<uint8_t>& getMemory();

private:

    //TODO: determine best way to provide fixed size to memory vector.
    vector<uint8_t> memory;
};

#endif // MEMORY_H

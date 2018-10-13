#include "VMContents.h"

//VMContents::VMContents()
//{
//    vmConstants;
//    vmLabels;
//    vmMemory;
////    vmRegisters;
//    vmVariables;
//}

//Constants& VMContents::getConstants()
//{
//    return vmConstants;
//}

//Labels& VMContents::getLabels()
//{
//    return vmLabels;
//}

//Memory& VMContents::getMemory()
//{
//    return vmMemory;
//}

////Registers& VMContents::getRegisters()
////{
////    return vmRegisters;
////}

//Variables& VMContents::getVariables()
//{
//    return vmVariables;
//}

//bool VMContents::processVariable(const string& variableName,
//                                 const string& variableValue,
//                                 unsigned variableSizeInBytes)
//{
//    if (!vmVariables.addVariable(variableName, variableSizeInBytes, variableValue))
//    {
//        return false;
//    }

//    unsigned byteCount = 0;
//    while (byteCount < variableSizeInBytes)
//    {
//        //TODO: process values (as bytes) into memory.

//        uint8_t currentByte = '0';
//        if (!vmMemory.addByteToMemory(currentByte))
//        {
//            return false;
//        }

//        ++byteCount;
//    }

//    return true;
//}

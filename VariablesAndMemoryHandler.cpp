//#include "VariablesAndMemoryHandler.h"

//VariablesAndMemoryHandler::VariablesAndMemoryHandler()
//{
//    memory;
//    variables;
//}

//bool VariablesAndMemoryHandler::processVariable(const string& variableName,
//                                 const string& variableValue,
//                                 unsigned variableSizeInBytes)
//{
//    if (!variables.addVariable(variableName, variableSizeInBytes, variableValue))
//    {
//        return false;
//    }

//    unsigned byteCount = 0;
//    while (byteCount < variableSizeInBytes)
//    {
//        //TODO: process values (as bytes) into memory.

//        uint8_t currentByte = '0';
//        if (!memory.addByteToMemory(currentByte))
//        {
//            return false;
//        }

//        ++byteCount;
//    }

//    return true;
//}

//Memory& VariablesAndMemoryHandler::getMemory()
//{
//    return memory;
//}

//Variables& VariablesAndMemoryHandler::getVariables()
//{
//    return variables;
//}

//void VariablesAndMemoryHandler::setMemory(const Memory& newMemory)
//{
//    memory = newMemory;
//}

//void VariablesAndMemoryHandler::setVariables(const Variables& newVariables)
//{
//    variables = newVariables;
//}

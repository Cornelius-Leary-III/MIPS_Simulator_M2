#include "VirtualMachine.h"

VirtualMachine::VirtualMachine()
{
    //    fileLexer;
    //    fileParser;
    //    instructionHandler;
    //    program;
    //    errorMessage;

    errorFlag = false;
    tokenizedSuccessfully = false;
    parsedSuccessfully = false;
    instructionsProcessedSuccessfully = false;
}

VirtualMachine::~VirtualMachine()
{
    if (contents)
    {
        delete contents;
        contents = nullptr;
    }
}

int VirtualMachine::userIOLoop(const string& fileToProcess)
{
    if (!setup(fileToProcess))
    {
        return EXIT_FAILURE;
    }

    string programInput;
    string printThisValue;

    while (cin >> programInput)
    {
        if (programInput == "print")
        {
            cin >> printThisValue;

            if (printThisValue[0] == '$')
            {
                stringstream ss;
                ss << "0x" << std::setfill('0') << std::setw(8)
                   << printRegisterContents(printThisValue);

                cout << ss.str() << endl;
            }
            else if (printThisValue[0] == '&')
            {
                string byteAddressTruncated =
                        printThisValue.substr(3, printThisValue.length() - 3);

                auto byteAddressInt = std::stoul(byteAddressTruncated);

                cout << printByteFromMemory(byteAddressInt) << endl;
            }
        }
        else if (programInput == "step")
        {
            executeCurrentStep();

            currentInstruction = contents->registersPtr->lookupRegister("pc")->second;

            stringstream ss;
            ss << "0x" << std::setfill('0') << std::setw(8) << currentInstruction;
            cout << ss.str() << endl;
        }
        else if (programInput == "quit")
        {
            break;
        }
    }

    return EXIT_SUCCESS;
}

bool VirtualMachine::setup(const string& inputFile)
{
    if (!tokenizeFile(inputFile))
    {
        return false;
    }

    if (!parseTokens())
    {
        return false;
    }

    if (!processInstructions())
    {
        return false;
    }

    return true;
}

bool VirtualMachine::tokenizeFile(const string& fileToTokenize)
{
    fileLexer.tokenizeFile(fileToTokenize);
    return !fileLexer.isErrorPresent();
}

bool VirtualMachine::parseTokens()
{
    fileParser.inputTokens(fileLexer.getTokens());
    return fileParser.parseStream();
}

bool VirtualMachine::processInstructions()
{
    instructionHandler.setVMContents(contents);

    if (!instructionHandler.processRawInstructions())
    {
        return false;
    }

    program = instructionHandler.getProgram();
    return !(program.empty());
}

bool VirtualMachine::checkForErrors()
{
    return errorFlag;
}

string& VirtualMachine::getErrorMessage()
{
    return errorMessage;
}

string VirtualMachine::printRegisterContents(const string& registerName)
{
    auto registerSet = contents->registersPtr;
    auto lookupIter = registerSet->lookupRegister(registerName);

    return std::to_string(lookupIter->second);
}

string VirtualMachine::printByteFromMemory(unsigned memoryAddress)
{
    auto memoryVector = contents->memoryPtr;

    stringstream ss;
    ss << "0x" << memoryVector->getByteFromMemory(memoryAddress);

    return ss.str();
}

void VirtualMachine::executeCurrentStep()
{
    auto programCounterIter = contents->registersPtr->lookupRegister("$pc");
    auto programCounter = (unsigned long) programCounterIter->second;

    program[programCounter]->execute(contents);
}





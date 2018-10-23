#include "InstructionParser.h"

InstructionParser::InstructionParser(const tokenVector& currentLineToParse,
                                     VMContents* newContentsPtr)
{
    lineOfTokens = currentLineToParse;
    currentToken = lineOfTokens.begin();
    lineEnd = lineOfTokens.end();
    contentsPtr = newContentsPtr;
}

bool InstructionParser::parse_Instruction()
{
    auto firstToken = currentToken;

    if (currentToken->type() == EOL)
    {
        return true;
    }
    else if (parse_LabelForInstruction())
    {
        ++currentToken;
        if (currentToken->type() == EOL)
        {
            //TODO: handle labels (i.e. jumps / branches)

            return true;
        }
    }

    if (parse_Operation())
    {
        ++currentToken;
        if (currentToken->type() == EOL)
        {
            addRawInstructionToSet();
            return true;
        }
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_Operation()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (currentToken->contents() == "nop")
    {
        return true;
    }

    if (parse_DataMovementInstruction())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;

    if (parse_IntegerArithmeticInstruction())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;

    if (parse_LogicalInstruction())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;

    if (parse_ControlInstruction())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_DataMovementInstruction()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (parse_DMI_2_args())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;

    if (parse_DMI_move())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_DMI_2_args()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (parse_DMI_2_args_load())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;

    if (parse_DMI_2_args_store())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_DMI_2_args_load()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    if (currentToken->contents() == "lw" ||
        currentToken->contents() == "lh" ||
        currentToken->contents() == "lb" ||
        currentToken->contents() == "la")
    {
        currentInstructionName = currentToken->contents();

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (!parse_MemoryReference())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        return true;
    }
    else if (currentToken->contents() == "li")
    {
        currentInstructionName = currentToken->contents();

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (!parse_Immediate())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        return true;
    }
    else
    {
        currentToken = firstToken;
        currentInstructionArguments = savedArguments;
        return false;
    }
}

bool InstructionParser::parse_DMI_2_args_store()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    if (currentToken->contents() == "sw" ||
        currentToken->contents() == "sh" ||
        currentToken->contents() == "sb")
    {
        currentInstructionName = currentToken->contents();

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (!parse_MemoryReference())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_DMI_move()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    if (currentToken->contents() == "move")
    {
        currentInstructionName = currentToken->contents();

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        return true;
    }
    else if (currentToken->contents() == "mfhi" ||
             currentToken->contents() == "mflo" ||
             currentToken->contents() == "mthi" ||
             currentToken->contents() == "mtlo")
    {
        currentInstructionName = currentToken->contents();

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_IntegerArithmeticInstruction()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (parse_IAI_2_args())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;

    if (parse_IAI_3_args())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;

    if (parse_IAI_div())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_IAI_3_args()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    if (currentToken->contents() == "add" ||
        currentToken->contents() == "addu" ||
        currentToken->contents() == "sub" ||
        currentToken->contents() == "subu" ||
        currentToken->contents() == "mul" ||
        currentToken->contents() == "mulo" ||
        currentToken->contents() == "mulou" ||
        currentToken->contents() == "rem" ||
        currentToken->contents() == "remu")
    {
        currentInstructionName = currentToken->contents();

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (!parse_Source())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_IAI_2_args()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    if (currentToken->contents() == "mult" ||
        currentToken->contents() == "multu" ||
        currentToken->contents() == "abs" ||
        currentToken->contents() == "neg" ||
        currentToken->contents() == "negu")
    {
        currentInstructionName = currentToken->contents();

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_IAI_div()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    if (currentToken->contents() == "div" ||
        currentToken->contents() == "divu")
    {
        currentInstructionName = currentToken->contents();

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken != lineEnd)
        {
            if (currentToken->type() == SEP)
            {
                ++currentToken;
                if (parse_Source())
                {
                    return true;
                }

                currentToken = firstToken;
                currentInstructionArguments = savedArguments;
                return false;
            }
        }

        --currentToken;
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_LogicalInstruction()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (parse_LI_3_args())
    {
        return true;
    }

    currentToken = firstToken;

    if (parse_LI_not())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_LI_3_args()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    if (currentToken->contents() == "and" ||
        currentToken->contents() == "nor" ||
        currentToken->contents() == "or" ||
        currentToken->contents() == "xor")
    {
        currentInstructionName = currentToken->contents();

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (!parse_Source())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_LI_not()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    if (currentToken->contents() == "not")
    {
        currentInstructionName = currentToken->contents();

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (!parse_Source())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_ControlInstruction()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (parse_CI_3_args())
    {
        return true;
    }

    currentToken = firstToken;

    if (parse_CI_jump())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_CI_3_args()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    if (currentToken->contents() == "beq" ||
        currentToken->contents() == "bne" ||
        currentToken->contents() == "blt" ||
        currentToken->contents() == "ble" ||
        currentToken->contents() == "bgt" ||
        currentToken->contents() == "bge")
    {
        currentInstructionName = currentToken->contents();

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (!parse_Source())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        ++currentToken;
        if (!parse_LabelForInstruction())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_CI_jump()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    if (currentToken->contents() == "j")
    {
        currentInstructionName = currentToken->contents();

        ++currentToken;
        if (!parse_LabelForInstruction())
        {
            currentToken = firstToken;
            currentInstructionArguments = savedArguments;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_MemoryReference()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

//    if (parse_LabelForInstruction())
//    {
//        return true;
//    }

//    currentToken = firstToken;

    currentToken = firstToken;

    string offset;

    if (currentToken->type() == STRING)
    {
        offset = currentToken->contents();
        ++currentToken;
    }

    if (currentToken->type() == OPEN_PAREN)
    {
        currentInstructionArguments.push_back(offset);
        ++currentToken;

        if (parse_Register())
        {
            ++currentToken;

            if (currentToken->type() == CLOSE_PAREN)
            {
                return true;
            }
        }
        else if (parse_Immediate())
        {
            ++currentToken;

            if (currentToken->type() == CLOSE_PAREN)
            {
                return true;
            }
        }
        else if (parse_Variable())
        {
            ++currentToken;

            if (currentToken->type() == CLOSE_PAREN)
            {
                return true;
            }
        }
    }
    else
    {
        --currentToken;

        if (parse_Source())
        {
            return true;
        }
        else if (parse_Variable())
        {
            return true;
        }
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_Source()
{
    auto firstToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    if (parse_Register())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;

    if (parse_Immediate())
    {
        return true;
    }

    currentToken = firstToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_LabelForInstruction()
{
    auto savedToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();
    auto contentChar = tokenContents.begin();
    auto contentEnd = tokenContents.end();

    if (!parse_Alpha(*contentChar))
    {
        currentToken = savedToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    ++contentChar;

    while (contentChar != contentEnd)
    {
        if (!parse_Alpha(*contentChar) &&
            !parse_Digit(*contentChar))
        {
            break;
        }
        ++contentChar;
    }

    if (*contentChar != ':')
    {
        currentToken = savedToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    auto nextAvailableInstructionAddress = (unsigned int) contentsPtr->programPtr->size() + 1;

    if (contentsPtr->labelsPtr->addLabel(tokenContents.substr(0, tokenContents.length() - 1),
                                         nextAvailableInstructionAddress))
    {
        return true;
    }

    currentToken = savedToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_Immediate()
{
    auto savedToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (parse_Immediate_Digits())
    {
        return true;
    }
    else if (parse_Immediate_Constant())
    {
        return true;
    }

    currentToken = savedToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_Immediate_Digits()
{
    auto savedToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();
    auto contentChar = tokenContents.begin();
    auto contentEnd = tokenContents.end();

    if (!parse_Digit(*contentChar))
    {
        currentToken = savedToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    ++contentChar;

    while (contentChar != contentEnd)
    {
        if (!parse_Digit(*contentChar))
        {
            currentToken = savedToken;
            currentInstructionArguments = savedArguments;
            return false;
        }
        ++contentChar;
    }

    currentInstructionArguments.push_back(tokenContents);
    return true;
}

bool InstructionParser::parse_Immediate_Constant()
{
    auto savedToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();
    auto contentChar = tokenContents.begin();
    auto contentEnd = tokenContents.end();

    if (!parse_Alpha(*contentChar))
    {
        currentToken = savedToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    ++contentChar;

    while (contentChar != contentEnd)
    {
        if (!parse_Alpha(*contentChar) &&
            !parse_Digit(*contentChar))
        {
            currentToken = savedToken;
            currentInstructionArguments = savedArguments;
            return false;
        }
        ++contentChar;
    }

    auto constantsEnd = contentsPtr->constantsPtr->getConstants().end();

    if (contentsPtr->constantsPtr->lookupConstant(tokenContents) != constantsEnd )
    {
        currentInstructionArguments.push_back(tokenContents);
        return true;
    }

    currentToken = savedToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_Register()
{
    auto savedToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();
    auto contentChar = tokenContents.begin();
    auto contentEnd = tokenContents.end();

    if (contentChar == contentEnd ||
        *contentChar != '$')
    {
        currentToken = savedToken;
        currentInstructionArguments = savedArguments;
        return false;
    }

    ++contentChar;

    while (contentChar != contentEnd)
    {
        if (!parse_Alpha(*contentChar) &&
            !parse_Digit(*contentChar))
        {
            currentToken = savedToken;
            currentInstructionArguments = savedArguments;
            return false;
        }
        ++contentChar;
    }

    return checkForValidRegisterName(tokenContents);
}

bool InstructionParser::parse_Variable()
{
    auto savedToken = currentToken;
    auto savedArguments = currentInstructionArguments;

    if (currentToken->type() != STRING)
    {
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();

    auto variableLookupIter = contentsPtr->variablesPtr->lookupVariable(tokenContents);
    if (variableLookupIter != contentsPtr->variablesPtr->getVariables().end())
    {
        currentInstructionArguments.push_back(tokenContents);
        return true;
    }

    currentToken = savedToken;
    currentInstructionArguments = savedArguments;
    return false;
}

bool InstructionParser::parse_Alpha(char currentChar)
{
    return isalpha(currentChar);
}

bool InstructionParser::parse_Digit(char currentChar)
{
    return isdigit(currentChar);
}

bool InstructionParser::parse_Char(char currentChar)
{
    return isprint(currentChar);
}

void InstructionParser::addRawInstructionToSet()
{
    RawInstruction newRawInstruction;
    newRawInstruction.setOperation(currentInstructionName);
    newRawInstruction.setArguments(currentInstructionArguments);
    newRawInstruction.setLine((unsigned int) currentToken->line());

    contentsPtr->programPtr->push_back(newRawInstruction);
}

bool InstructionParser::checkForValidRegisterName(const string& registerName)
{
    string registerNameNoDollarSign = registerName.substr(1, registerName.length() - 1);
    if (checkForValidRegisterNumber(registerNameNoDollarSign))
    {
        currentInstructionArguments.push_back(registerName);
        return true;
    }

    auto nameLookupIter = contentsPtr->validRegisterNamesMapPtr->find(registerName);
    if ( nameLookupIter != contentsPtr->validRegisterNamesMapPtr->end())
    {
        currentInstructionArguments.push_back(nameLookupIter->second);
        return true;
    }

    return false;
}

bool InstructionParser::checkForValidRegisterNumber(const string& registerNumber)
{
    char firstCharInRegisterName = registerNumber[0];

    if (parse_Digit(firstCharInRegisterName))
    {
        if (registerNumber.length() > 2)
        {
            return false;
        }
        else if (registerNumber.length() == 1)
        {
            return true;
        }
        else if (registerNumber.length() == 2)
        {
            if (firstCharInRegisterName > 3)
            {
                return false;
            }
            else if (firstCharInRegisterName == 3)
            {
                char secondDigitInRegisterName = registerNumber[1];
                if (secondDigitInRegisterName > 1)
                {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

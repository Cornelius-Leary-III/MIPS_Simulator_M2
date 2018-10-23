#include "DeclarationParser.h"

DeclarationParser::DeclarationParser(const tokenVector& currentLineToParse,
                                     VMContents* newContentsPtr)
{
    lineOfTokens = currentLineToParse;
    currentToken = lineOfTokens.begin();
    contentsPtr = newContentsPtr;

    variableName;
    variableLayout;
    variableValue;
}

bool DeclarationParser::parse_Declaration()
{
    auto firstToken = currentToken;

    if (parse_Constant())
    {
        ++currentToken;
        if (currentToken->type() == EOL)
        {
            return true;
        }
    }
    else
    {
        currentToken = firstToken;
    }

    if (parse_Variable())
    {
        ++currentToken;
        if (parse_Layout())
        {
            ++currentToken;
            if (currentToken->type() == EOL)
            {
                return processLayout();
            }
        }
    }

    currentToken = firstToken;
    return false;
}

bool DeclarationParser::parse_Constant()
{   
    auto savedToken = currentToken;
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
        return false;
    }

    ++contentChar;

    while (contentChar != contentEnd)
    {
        if (!parse_Alpha(*contentChar) &&
            !parse_Digit(*contentChar))
        {
            currentToken = savedToken;
            return false;
        }
        ++contentChar;
    }
    string constantName = currentToken->contents();

    ++currentToken;

    if (currentToken->type() != EQUAL)
    {
        currentToken = savedToken;
        return false;
    }

    ++currentToken;

    if (!parse_Integer())
    {
        currentToken = savedToken;
        return false;
    }

    int constantValue = std::stoi(currentToken->contents());
    return contentsPtr->constantsPtr->addConstant(constantName, constantValue);
}

bool DeclarationParser::parse_Variable()
{
    auto savedToken = currentToken;
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
        return false;
    }

    string variableContents = currentToken->contents();
    variableName = variableContents.substr(0, variableContents.length() - 1);

    return true;
}

bool DeclarationParser::parse_Layout()
{
    auto savedToken = currentToken;
    auto tokensEnd = lineOfTokens.end();

    if (parse_IntLayout())
    {
        variableLayout = currentToken->contents();
        ++currentToken;

        if (parse_Integer())
        {
            variableValue = currentToken->contents();
            ++currentToken;

            return true;
        }
    }

    currentToken = savedToken;

    if (parse_StringLayout())
    {
        variableLayout = currentToken->contents();
        ++currentToken;

        if (parse_String())
        {
            ++currentToken;
            return true;
        }
    }

    currentToken = savedToken;
    return false;
}

bool DeclarationParser::parse_IntLayout()
{
    auto savedToken = currentToken;
    if (currentToken->type() != STRING)
    {
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();

    if (tokenContents == ".word" ||
        tokenContents == ".half" ||
        tokenContents == ".byte" ||
        tokenContents == ".space")
    {
        return true;
    }

    currentToken = savedToken;
    return false;
}

bool DeclarationParser::parse_StringLayout()
{
    auto savedToken = currentToken;
    if (currentToken->type() != STRING)
    {
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();

    if (tokenContents == ".ascii" ||
        tokenContents == ".asciiz")
    {
        return true;
    }

    currentToken = savedToken;
    return false;
}

bool DeclarationParser::parse_Integer()
{
    auto savedToken = currentToken;
    if (currentToken->type() != STRING)
    {
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();

    auto currentChar = tokenContents.begin();
    auto charEnd = tokenContents.end();

    if (*currentChar == '+')
    {
        ++currentChar;
    }
    else if (*currentChar == '-')
    {
        ++currentChar;
    }

    while (currentChar != charEnd)
    {
        if (!parse_Digit(*currentChar))
        {
            currentToken = savedToken;
            return false;
        }

        ++currentChar;
    }

    return true;
}

bool DeclarationParser::parse_String()
{
    auto savedToken = currentToken;
    if (currentToken->type() != STRING_DELIM)
    {
        return false;
    }

    ++currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = savedToken;
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();

    auto currentChar = tokenContents.begin();
    auto charEnd = tokenContents.end();

    while (currentChar != charEnd)
    {
        if (!parse_Char(*currentChar))
        {
            currentToken = savedToken;
            return false;
        }

        ++currentChar;
    }

    variableValue = currentToken->contents();

    ++currentToken;
    if (currentToken->type() != STRING_DELIM)
    {
        currentToken = savedToken;
        return false;
    }

    return true;
}

bool DeclarationParser::parse_Alpha(char currentChar)
{
    return isalpha(currentChar);
}

bool DeclarationParser::parse_Digit(char currentChar)
{
    return isdigit(currentChar);
}

bool DeclarationParser::parse_Char(char currentChar)
{
    return isprint(currentChar);
}

bool DeclarationParser::processLayout()
{
    if (variableLayout != ".space")
    {
        if (!contentsPtr->variablesPtr->addVariable(variableName, determineVariableSize(), variableValue))
        {
            return false;
        }

        //TODO: determine how to break a variable's value / etc. into bytes to put into memory.
        uint8_t currentByte = '0';

        //TODO: add loop here to repeat this byte-adding process.
        if (!contentsPtr->memoryPtr->addByteToMemory(currentByte))
        {
            return false;
        }

        return true;
    }
    else
    {
        //TODO: just add 0's here for blank spaces when ".space" is chosen.

        //TODO: determine how to break a variable's value / etc. into bytes to put into memory.
        uint8_t currentByte = '0';

        //TODO: add loop here to repeat this byte-adding process.
        if (!contentsPtr->memoryPtr->addByteToMemory(currentByte))
        {
            return false;
        }

        return true;
    }
}

unsigned DeclarationParser::determineVariableSize()
{
    unsigned variableSize;
    if (variableLayout == ".word")
    {
        variableSize = 4;
    }
    else if (variableLayout == ".half")
    {
        variableSize = 2;
    }
    else if (variableLayout == ".byte")
    {
        variableSize = 1;
    }
    else if (variableLayout == ".space")
    {
        variableSize = (unsigned) std::stoi(variableValue);
    }
    else if (variableLayout == ".ascii")
    {
        variableSize = variableValue.length();
    }
    else if (variableLayout == ".asciiz")
    {
        variableSize = variableValue.length() + 1;
    }
    else
    {
        variableSize = 0;
    }

    return variableSize;
}












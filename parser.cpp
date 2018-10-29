#include "parser.h"

parser::parser()
{
    currentLineNum = 1;

    streamParsedSafely = true;
    dataGrammarActive = false;
    textGrammarActive = false;
    declarationProcessor = nullptr;
    instructionProcessor = nullptr;

    contentsPtr = nullptr;
}

void parser::setContents(VMContents* newContents)
{
    contentsPtr = newContents;
}

void parser::inputTokens(const tokenVector& newTokens)
{
    tokenStream = newTokens;

    auto firstToken = tokenStream.begin();
    if (!tokenStream.empty())
    {
        currentLineNum = firstToken->line();
    }
    else
    {
        currentLineNum = 1;
    }

    tokenIter = tokenStream.begin();
    tokensEnd = tokenStream.end();

    groupTokensByLine();
    fileLineIter = fileSplitUpByLines.begin();
    fileEnd = fileSplitUpByLines.end();
}

bool parser::parseStream()
{
    while (fileLineIter != fileEnd &&
           streamParsedSafely)
    {
        if (checkForGrammarChanges())
        {

        }
        else if (dataGrammarActive)
        {
            streamParsedSafely = dataGrammarParsing();
        }
        else if (textGrammarActive)
        {
            streamParsedSafely = textGrammarParsing();
        }
        else
        {

        }

        ++fileLineIter;
    }

    return streamParsedSafely;
}

void parser::groupTokensByLine()
{
    size_t lineInFile = tokenIter->line();

    while (tokenIter != tokensEnd)
    {
        if (tokenIter->line() == lineInFile)
        {
            tokensOnCurrentLine.push_back(*tokenIter);
            ++tokenIter;
        }
        else
        {
            fileSplitUpByLines.push_back(tokensOnCurrentLine);
            tokensOnCurrentLine.clear();

            lineInFile = tokenIter->line();
        }
    }

    if (!tokensOnCurrentLine.empty())
    {
        fileSplitUpByLines.push_back(tokensOnCurrentLine);
    }
}

bool parser::dataGrammarParsing()
{
    if (declarationProcessor != nullptr)
    {
        delete declarationProcessor;
        declarationProcessor = nullptr;
    }

    declarationProcessor = new DeclarationParser(*fileLineIter, contentsPtr);
    return declarationProcessor->parse_Declaration();
}

bool parser::textGrammarParsing()
{
    if (instructionProcessor != nullptr)
    {
        delete instructionProcessor;
        instructionProcessor = nullptr;
    }

    instructionProcessor = new InstructionParser(*fileLineIter, contentsPtr);
    return instructionProcessor->parse_Instruction();
}


bool parser::checkForGrammarChanges()
{
    if (checkIfDataGrammar())
    {
        dataGrammarActive = true;
        textGrammarActive = false;
    }
    else if (checkIfTextGrammar())
    {
        dataGrammarActive = false;
        textGrammarActive = true;
    }
    else
    {
        return false;
    }

    return true;
}

bool parser::checkIfDataGrammar()
{
    auto localTokenIter = fileLineIter->begin();

    if (localTokenIter->type() != STRING)
    {
        return false;
    }

    if (localTokenIter->contents() != ".data")
    {
        return false;
    }

    if ((++localTokenIter)->type() != EOL)
    {
        return false;
    }

    return true;
}

bool parser::checkIfTextGrammar()
{
    auto localTokenIter = fileLineIter->begin();

    if (localTokenIter->type() != STRING)
    {
        return false;
    }

    if (localTokenIter->contents() != ".text")
    {
        return false;
    }

    if ((++localTokenIter)->type() != EOL)
    {
        return false;
    }

    return true;
}


VMContents* parser::getContents()
{
    return contentsPtr;
}

#include "parser.h"

parser::parser(std::istream& streamToParse)
{
    tokenizer.tokenizeStream(streamToParse);
    tokenStream = tokenizer.getTokens();

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

    tokensOnCurrentLine;

    streamParsedSafely = true;
    dataGrammarActive = false;
    textGrammarActive = false;
    declarationProcessor = nullptr;
    instructionProcessor = nullptr;

    groupTokensByLine();
    fileLineIter = fileSplitUpByLines.begin();
    fileEnd = fileSplitUpByLines.end();

    contentsPtr = new VMContents();

    contentsPtr->constantsPtr = new Constants();
    contentsPtr->labelsPtr = new Labels();
    contentsPtr->memoryPtr = new Memory();
    contentsPtr->variablesPtr = new Variables();
    contentsPtr->programPtr = new vector<RawInstruction>();

    map<string, string> validRegisterNamesMap;
    validRegisterNamesMap.emplace("$zero", "$0");
    validRegisterNamesMap.emplace("$at", "$1");
    validRegisterNamesMap.emplace("$v0", "$2");
    validRegisterNamesMap.emplace("$v1", "$3");
    validRegisterNamesMap.emplace("$a0", "$4");
    validRegisterNamesMap.emplace("$a1", "$5");
    validRegisterNamesMap.emplace("$a2", "$6");
    validRegisterNamesMap.emplace("$a3", "$7");
    validRegisterNamesMap.emplace("$t0", "$8");
    validRegisterNamesMap.emplace("$t1", "$9");
    validRegisterNamesMap.emplace("$t2", "$10");
    validRegisterNamesMap.emplace("$t3", "$11");
    validRegisterNamesMap.emplace("$t4", "$12");
    validRegisterNamesMap.emplace("$t5", "$13");
    validRegisterNamesMap.emplace("$t6", "$14");
    validRegisterNamesMap.emplace("$t7", "$15");
    validRegisterNamesMap.emplace("$s0", "$16");
    validRegisterNamesMap.emplace("$s1", "$17");
    validRegisterNamesMap.emplace("$s2", "$18");
    validRegisterNamesMap.emplace("$s3", "$19");
    validRegisterNamesMap.emplace("$s4", "$20");
    validRegisterNamesMap.emplace("$s5", "$21");
    validRegisterNamesMap.emplace("$s6", "$22");
    validRegisterNamesMap.emplace("$s7", "$23");
    validRegisterNamesMap.emplace("$t8", "$24");
    validRegisterNamesMap.emplace("$t9", "$25");
    validRegisterNamesMap.emplace("$k0", "$26");
    validRegisterNamesMap.emplace("$k1", "$27");
    validRegisterNamesMap.emplace("$gp", "$28");
    validRegisterNamesMap.emplace("$sp", "$29");
    validRegisterNamesMap.emplace("$fp", "$30");
    validRegisterNamesMap.emplace("$ra", "$31");

    contentsPtr->validRegisterNamesMapPtr = &validRegisterNamesMap;
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




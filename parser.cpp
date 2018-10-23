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
    contentsPtr->validRegisterNamesMapPtr = new map<string, string>();

    contentsPtr->validRegisterNamesMapPtr->emplace("$zero", "$0");
    contentsPtr->validRegisterNamesMapPtr->emplace("$at", "$1");
    contentsPtr->validRegisterNamesMapPtr->emplace("$v0", "$2");
    contentsPtr->validRegisterNamesMapPtr->emplace("$v1", "$3");
    contentsPtr->validRegisterNamesMapPtr->emplace("$a0", "$4");
    contentsPtr->validRegisterNamesMapPtr->emplace("$a1", "$5");
    contentsPtr->validRegisterNamesMapPtr->emplace("$a2", "$6");
    contentsPtr->validRegisterNamesMapPtr->emplace("$a3", "$7");
    contentsPtr->validRegisterNamesMapPtr->emplace("$t0", "$8");
    contentsPtr->validRegisterNamesMapPtr->emplace("$t1", "$9");
    contentsPtr->validRegisterNamesMapPtr->emplace("$t2", "$10");
    contentsPtr->validRegisterNamesMapPtr->emplace("$t3", "$11");
    contentsPtr->validRegisterNamesMapPtr->emplace("$t4", "$12");
    contentsPtr->validRegisterNamesMapPtr->emplace("$t5", "$13");
    contentsPtr->validRegisterNamesMapPtr->emplace("$t6", "$14");
    contentsPtr->validRegisterNamesMapPtr->emplace("$t7", "$15");
    contentsPtr->validRegisterNamesMapPtr->emplace("$s0", "$16");
    contentsPtr->validRegisterNamesMapPtr->emplace("$s1", "$17");
    contentsPtr->validRegisterNamesMapPtr->emplace("$s2", "$18");
    contentsPtr->validRegisterNamesMapPtr->emplace("$s3", "$19");
    contentsPtr->validRegisterNamesMapPtr->emplace("$s4", "$20");
    contentsPtr->validRegisterNamesMapPtr->emplace("$s5", "$21");
    contentsPtr->validRegisterNamesMapPtr->emplace("$s6", "$22");
    contentsPtr->validRegisterNamesMapPtr->emplace("$s7", "$23");
    contentsPtr->validRegisterNamesMapPtr->emplace("$t8", "$24");
    contentsPtr->validRegisterNamesMapPtr->emplace("$t9", "$25");
    contentsPtr->validRegisterNamesMapPtr->emplace("$k0", "$26");
    contentsPtr->validRegisterNamesMapPtr->emplace("$k1", "$27");
    contentsPtr->validRegisterNamesMapPtr->emplace("$gp", "$28");
    contentsPtr->validRegisterNamesMapPtr->emplace("$sp", "$29");
    contentsPtr->validRegisterNamesMapPtr->emplace("$fp", "$30");
    contentsPtr->validRegisterNamesMapPtr->emplace("$ra", "$31");

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




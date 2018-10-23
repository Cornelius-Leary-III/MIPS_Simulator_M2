#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "DeclarationParser.h"
#include "InstructionParser.h"

#include "VariablesAndMemoryHandler.h"
#include "VMContents.h"

#include "VMContents.h"

#include <map>
using std::map;

#include <vector>
using std::vector;

#include <sstream>
using std::stringstream;


class parser
{
public:

    parser(std::istream& streamToParse);

    bool parseStream();

    bool checkForGrammarChanges();
    bool checkIfDataGrammar();
    bool checkIfTextGrammar();

    bool dataGrammarParsing();
    bool textGrammarParsing();

    Constants& getConstants();
    Labels& getLabels();
    Memory& getMemory();

private:

    void getAllTokensOnCurrentLine();
    void updateTokenIter();
    void groupTokensByLine();

    vector<tokenVector> fileSplitUpByLines;
    vector<tokenVector>::iterator fileLineIter;
    vector<tokenVector>::iterator fileEnd;

    lexer tokenizer;
    DeclarationParser* declarationProcessor;
    InstructionParser* instructionProcessor;

    tokenVector::iterator tokenIter;
    tokenVector::iterator tokensEnd;
    tokenVector tokenStream;
    tokenVector tokensOnCurrentLine;
    size_t currentLineNum;

    bool dataGrammarActive;
    bool textGrammarActive;
    bool streamParsedSafely;

    VMContents* contentsPtr;

    // vector<Instruction*> program;

};

#endif // PARSER_H

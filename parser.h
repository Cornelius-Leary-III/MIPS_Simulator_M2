#ifndef PARSER_H
#define PARSER_H

#include "token.h"
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

    parser();
    ~parser();

    void inputTokens(const tokenVector& newTokens);
    bool parseStream();
    void setContents(VMContents* newContents);
    VMContents* getContents();

private:

    bool checkForGrammarChanges();
    bool checkIfDataGrammar();
    bool checkIfTextGrammar();
    bool dataGrammarParsing();
    bool textGrammarParsing();
    void getAllTokensOnCurrentLine();
    void updateTokenIter();
    void groupTokensByLine();

    vector<tokenVector> fileSplitUpByLines;
    vector<tokenVector>::iterator fileLineIter;
    vector<tokenVector>::iterator fileEnd;

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
};

#endif // PARSER_H

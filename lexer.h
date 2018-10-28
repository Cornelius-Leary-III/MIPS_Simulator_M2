#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <istream>
#include <fstream>
#include <sstream>

using std::string;

class lexer
{
public:

    lexer();

    void tokenizeFile(const string& inputFile);
    void tokenizeStream(std::istream& input);

    tokenVector& getTokens();

    bool isStringDelimiterErrorPresent();
    bool isParenthesesErrorPresent();
    bool isErrorPresent();

protected:

    tokenVector tokenizedText;

    size_t currentTokenId;
    size_t currentLine;
    string currentCharSequence;

    bool withinComment;
    bool withinString;
    int parenthesesDepth;

    bool stringDelimiterError;
    bool parenthesesError;

private:

    bool isCurrentCharSequenceNotEmpty();
    void updateLexerStateAfterNewlineChar();
    void updateLexerStateAtEndOfStream(char finalChar);

    void processCharWithinString(char currentChar);
    void processCharWithinComment(char currentChar);
    void processCharOutsideOfString(char currentChar);

    void handleEOL();
    void handleWhitespace();

    void addTokenWithoutContents(TokenType currentTokenType);
    void handleSEP();
    void handleEQUAL();
    void handleOPEN_PAREN();
    void handleCLOSE_PAREN();
    void handleSTRING_DELIM();

    void addTokenSTRING();
    void handleSTRING();

    void addTokenStringDelimiterError();
    void addTokenParenthesesError();
    void handleERROR();
};

#endif // LEXER_H

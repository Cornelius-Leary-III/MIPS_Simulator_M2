#ifndef DECLARATIONPARSER_H
#define DECLARATIONPARSER_H

#include "token.h"
#include <string>

#include "VMContents.h"

using std::string;

class DeclarationParser
{
public:
    DeclarationParser(const tokenVector& currentLineToParse,
                      VMContents* newContentsPtr);

    bool parse_Declaration();
    bool parse_Constant();
    bool parse_Variable();
    bool parse_Layout();
    bool parse_IntLayout();
    bool parse_StringLayout();
    bool parse_Integer();
    bool parse_String();
    bool parse_Digit(char currentChar);
    bool parse_Alpha(char currentChar);
    bool parse_Char(char currentChar);

    unsigned determineVariableSize();
    bool processLayout();

private:

    tokenVector lineOfTokens;
    tokenVector::iterator currentToken;
    VMContents* contentsPtr;

    string variableName;
    string variableLayout;
    string variableValue;
};

#endif // DECLARATIONPARSER_H

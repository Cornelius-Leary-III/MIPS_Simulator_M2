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
    bool parse_Label();
    bool parse_Layout();
    bool parse_IntLayout();
    bool parse_StringLayout();
    bool parse_Integer();
    bool parse_String();
    bool parse_Digit(char currentChar);
    bool parse_Alpha(char currentChar);
    bool parse_Char(char currentChar);

private:

    tokenVector lineOfTokens;
    tokenVector::iterator currentToken;
    VMContents* contentsPtr;

};

#endif // DECLARATIONPARSER_H

#include "Constants.h"


//TODO: implement appropriate constructor(s).
Constants::Constants()
{
    constants;
}

//TODO: implement method to add constant to map.
bool Constants::addConstant(const string& constantName, int constantValue)
{
    return true;
}

//TODO: implement constant lookup method.
map<string, int>::iterator Constants::lookupConstant(const string& constantName)
{
    return constants.begin();
}

//TODO: implement setting constants to entirely-new map of constants.
void Constants::setConstants(const map<string, int>& newConstants)
{
    return;
}

map<string, int>& Constants::getConstants()
{
    return constants;
}

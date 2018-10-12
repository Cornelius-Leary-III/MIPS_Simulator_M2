#include "Constants.h"


//TODO: implement appropriate constructor(s).
Constants::Constants()
{
    constants;
    constantsEnd = constants.end();
}

Constants::Constants(const vector<string>& nameVector,
                     const vector<int>& valueVector)
{
    constants;
    constantsEnd = constants.end();

    auto nameIter = nameVector.begin();
    auto namesEnd = nameVector.end();

    auto valueIter = valueVector.begin();
    auto valuesEnd = valueVector.end();

    while (nameIter != namesEnd &&
           valueIter != valuesEnd)
    {
        if (!addConstant(*nameIter, *valueIter))
        {
            break;
        }

        ++nameIter;
        ++valueIter;
    }
}

bool Constants::addConstant(const string& constantName, int constantValue)
{
    auto insertIter = constants.insert(make_pair(constantName, constantValue));
    return insertIter.second;
}

map<string, int>::iterator Constants::lookupConstant(const string& constantName)
{
    auto lookupIter = constants.find(constantName);
    if (lookupIter != constantsEnd)
    {
        return lookupIter;
    }

    return constantsEnd;
}

void Constants::setConstants(const map<string, int>& newConstants)
{
    constants = newConstants;
}

map<string, int>& Constants::getConstants()
{
    return constants;
}

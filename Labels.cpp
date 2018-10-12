#include "Labels.h"

Labels::Labels()
{
    labels;
}

bool Labels::addLabel(const string& labelName,
                      const string& labelType,
                      unsigned labelAddress)
{
    auto innerPair = make_pair(labelType, labelAddress);
    auto outerPair = make_pair(labelName, innerPair);
    auto insertIter = labels.insert(outerPair);

    return insertIter.second;
}

map<string, pair<string, unsigned>>::iterator
    Labels::lookupLabel(const string& labelName)
{
    auto lookupIter = labels.find(labelName);
    if (lookupIter != labelsEnd)
    {
        return lookupIter;
    }

    return labelsEnd;
}

void Labels::setLabels(const map<string, pair<string, unsigned>>& newLabels)
{
    labels = newLabels;
}

map<string, pair<string, unsigned>>& Labels::getLabels()
{
    return labels;
}

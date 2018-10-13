#include "Labels.h"

Labels::Labels()
{
    labels;
    labelsEnd = labels.end();
}

bool Labels::addLabel(const string& labelName, unsigned labelAddress)
{
    auto insertIter = labels.insert(make_pair(labelName, labelAddress));
    return insertIter.second;
}

map<string, unsigned>::iterator Labels::lookupLabel(const string& labelName)
{
    auto lookupIter = labels.find(labelName);
    if (lookupIter != labelsEnd)
    {
        return lookupIter;
    }

    return labelsEnd;
}

void Labels::setLabels(const map<string, unsigned>& newLabels)
{
    labels = newLabels;
}

map<string, unsigned>& Labels::getLabels()
{
    return labels;
}


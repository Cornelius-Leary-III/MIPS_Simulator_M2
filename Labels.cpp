#include "Labels.h"

//TODO: implement appropriate constructor(s).
Labels::Labels()
{

}

//TODO: implement method to add label to map.
bool Labels::addLabel(const string& labelName,
                      const string& labelType,
                      unsigned labelAddress)
{
    return true;
}

//TODO: implement method to lookup label.
map<string, pair<string, unsigned>>::iterator
    Labels::lookupLabel(const string& labelName)
{
    return labels.begin();
}

//TODO: implement method to set labels to entirely-new map of labels.
void Labels::setLabels(const map<string, pair<string, unsigned>>& newLabels)
{
    return;
}

map<string, pair<string, unsigned>>& Labels::getLabels()
{
    return labels;
}

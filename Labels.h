#ifndef LABELS_H
#define LABELS_H

#include <map>
#include <string>

using std::map;
using std::pair;
using std::make_pair;
using std::string;

class Labels
{
public:
    Labels();

    bool addLabel(const string& labelName, unsigned labelAddress);
    map<string, unsigned>::iterator lookupLabel(const string& labelName);
    void setLabels(const map<string, unsigned>& newLabels);
    map<string, unsigned>& getLabels();

private:
    map<string, unsigned> labels;
    map<string, unsigned>::iterator labelsEnd;
};

#endif // LABELS_H

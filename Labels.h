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

    bool addLabel(const string& labelName,
                  const string& labelType,
                  unsigned labelAddress);
    map<string, pair<string, unsigned>>::iterator lookupLabel(const string& labelName);
    void setLabels(const map<string, pair<string, unsigned>>& newLabels);
    map<string, pair<string, unsigned>>& getLabels();

private:
    map<string, pair<string, unsigned>> labels;
};

#endif // LABELS_H

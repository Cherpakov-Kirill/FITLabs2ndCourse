#ifndef LAB2_REPLACE_H
#define LAB2_REPLACE_H
#include "worker.h"

class replaceBlock: public worker{
private:
    string oldWord;
    string newWord;
public:
    replaceBlock(string &firstWord,string &secondWord);
    bool execute(vector<string> &input, vector<string> &output, bool inputData) override;
};

#endif //LAB2_REPLACE_H

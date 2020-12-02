#ifndef LAB2_GREP_H
#define LAB2_GREP_H
#include "worker.h"

class grepBlock: public worker {
private:
    string grepWord;
public:
    explicit grepBlock(string &word);
    bool execute(vector<string> &input, vector<string> &output, bool inputData) override;
};


#endif //LAB2_GREP_H

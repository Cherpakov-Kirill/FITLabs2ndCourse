#ifndef LAB2_READFILE_H
#define LAB2_READFILE_H
#include "worker.h"

class readFileBlock: public worker {
private:
    string readFileName;
public:
    explicit readFileBlock(string &file);
    bool execute(vector<string> &input, vector<string> &output, bool inputData) override;
};

#endif //LAB2_READFILE_H

#ifndef LAB2_WRITEFILE_H
#define LAB2_WRITEFILE_H
#include "worker.h"

class writeFileBlock: public worker {
private:
    string writeFileName;
public:
    writeFileBlock(string &file);
    bool execute(vector<string> &input, vector<string> &output, bool inputData) override;
};


#endif //LAB2_WRITEFILE_H

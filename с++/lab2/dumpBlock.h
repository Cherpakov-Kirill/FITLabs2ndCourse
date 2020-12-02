#ifndef LAB2_DUMP_H
#define LAB2_DUMP_H
#include "worker.h"

class dumpBlock: public worker {
private:
    string dumpFilename;
public:
    explicit dumpBlock(string &file);
    bool execute(vector<string> &input, vector<string> &output, bool inputData) override;
};


#endif //LAB2_DUMP_H

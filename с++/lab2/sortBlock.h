#ifndef LAB2_SORT_H
#define LAB2_SORT_H
#include "worker.h"

class sortBlock: public worker {
public:
    sortBlock() = default;
    bool execute(vector<string> &input, vector<string> &output, bool inputData) override;
};

#endif //LAB2_SORT_H

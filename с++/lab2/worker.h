#ifndef LAB2_WORKER_H
#define LAB2_WORKER_H

#include <algorithm>
#include <fstream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
typedef unsigned int uint;

class worker {
public:
    virtual bool execute(vector<string> &input, vector<string> &output, bool inputData) = 0; //return outData boot true
};

#endif //LAB2_WORKER_H

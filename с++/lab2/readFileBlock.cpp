#include "readFileBlock.h"

readFileBlock::readFileBlock(string &file) {
    readFileName = file;
}

bool readFileBlock::execute(vector<string> &input, vector<string> &output, bool inputData) {
    if(inputData) throw logic_error("Read file is on incorrect place in queue of blocks!");
    ifstream fin(readFileName);
    string newString;
    getline(fin, newString);
    while(!fin.eof()){
        output.push_back(newString);
        getline(fin, newString);
    }
    fin.close();
    return true; ///true - if out data; false - if no out data
}



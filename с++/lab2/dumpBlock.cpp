#include "dumpBlock.h"

dumpBlock::dumpBlock(string &file) {
    dumpFilename = file;
}

bool dumpBlock::execute(vector<string> &input, vector<string> &output, bool inputData) {
    if(!inputData) throw logic_error("No input stream for block!");
    ofstream fout(dumpFilename);
    for(string& s : input) fout<<s<<endl;
    fout.close();
    return true;
}

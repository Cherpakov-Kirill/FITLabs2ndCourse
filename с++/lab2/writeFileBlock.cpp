#include "writeFileBlock.h"

writeFileBlock::writeFileBlock(string &file) {
    writeFileName=file;
}

bool writeFileBlock::execute(vector<string> &input, vector<string> &output, bool inputData) {
    ofstream fout(writeFileName);
    for(string& s : input) fout<<s<<endl;
    fout.close();
    return false;
}

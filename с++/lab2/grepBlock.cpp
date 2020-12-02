#include "grepBlock.h"

grepBlock::grepBlock(string &word) {
    grepWord = word;
}

bool grepBlock::execute(vector<string> &input, vector<string> &output, bool inputData) {
    if(!inputData) throw logic_error("No input stream for block!");
    auto it = output.begin();
    while(it!=output.end()){
        int pos = (*it).find(grepWord);
        if(pos == string::npos){
            output.erase(it);
        }
        else it++;
    }
    return true;
}

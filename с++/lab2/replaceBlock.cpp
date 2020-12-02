#include "replaceBlock.h"

replaceBlock::replaceBlock(string &firstWord, string &secondWord) {
    oldWord = firstWord;
    newWord = secondWord;
}

bool replaceBlock::execute(vector<string> &input, vector<string> &output, bool inputData) {
    if(!inputData) throw logic_error("No input stream for block!");
    for(string& s : output){
        int pos = s.find(oldWord);
        if(pos != string::npos){
            s.replace(pos, oldWord.length(), newWord);
        }
    }
    return true;
}

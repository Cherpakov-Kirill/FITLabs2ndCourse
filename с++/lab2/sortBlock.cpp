#include "sortBlock.h"

bool comparator(string a, string b){
    ///false - b is lower then a
    ///true - a is lower then b
    for(int i=0;i<a.length();i++){
        if(i>=b.length()){
            return false;
        }
        int first = tolower(a[i]);
        int second = tolower(b[i]);
        if(first<second) return true;
        else if(first>second) return false;
    }
    return true;
}

bool sortBlock::execute(vector<string> &input, vector<string> &output, bool inputData) {
    sort(output.begin(),output.end(),comparator);
    return true;
}

#include "CSVParser.h"

using namespace std;

int main(){
    ifstream a("input.csv");

    CSVParser<int, string> parser(a,0/*skip first lines count*/);
    parser.changeSeparators('"',',','\n');

    for(tuple<int, string> rs : parser) cout << rs << endl;
    return 0;
}
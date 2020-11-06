#include "countingWords.h"

int main(int argc, char** argv) {
    countingWords parsingWords;
    parsingWords.openingFStream(argv);
    parsingWords.parsingWordsFromInputToOutput();
    parsingWords.closingFStream();
    return 0;
}

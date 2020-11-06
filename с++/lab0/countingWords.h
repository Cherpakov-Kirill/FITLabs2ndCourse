#ifndef LAB0_COUNTINGWORDS_H
#define LAB0_COUNTINGWORDS_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

class countingWords
{
private:
    int counterOfAllWords;
    std::map<std::string, int> mapForWords;
    std::ifstream F_in;
    std::ofstream F_out;

    void readingAndCountingWords();
    void sortingWordsAndWritingToOutputFile();
    static bool checkingTheLetter(char symbol);
    static bool checkingTheNumber(char symbol);
    static bool comparatorForSort(const std::pair<std::string,int> &a, const std::pair<std::string,int> &b);

public:
    countingWords();
    void openingFStream(char **arg);
    void closingFStream();
    void parsingWordsFromInputToOutput();
};
#endif //LAB0_COUNTINGWORDS_H

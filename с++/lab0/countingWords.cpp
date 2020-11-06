#include "countingWords.h"

    bool countingWords::comparatorForSort(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
        return a.second > b.second;
    }

    countingWords::countingWords() {
        counterOfAllWords = 0;
    }

    bool countingWords::checkingTheLetter(char symbol){
        if((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')) return true;
        else return false;
    }
    bool countingWords::checkingTheNumber(char symbol){
        if(symbol >= '0' && symbol <= '9') return true;
        else return false;
    }

    void countingWords::openingFStream(char **arg){
        F_in.open(arg[1]);
        F_out.open(arg[2]);
    }

    void countingWords::closingFStream(){
        F_in.close();
        F_out.close();
    }

    void countingWords::parsingWordsFromInputToOutput(){
        readingAndCountingWords();
        sortingWordsAndWritingToOutputFile();
    }

    void countingWords::readingAndCountingWords(){
        std::string stringGet, newWord;
        bool previousSymbolWasInLetter = true;
        while(getline(F_in, stringGet)){
            for(char currentSymbol : stringGet){
                if(checkingTheLetter(currentSymbol) || checkingTheNumber(currentSymbol)){
                    newWord += currentSymbol;
                    previousSymbolWasInLetter = true;
                }
                else{
                    if(previousSymbolWasInLetter) {
                        mapForWords[newWord]++;
                        counterOfAllWords++;
                        newWord = "";
                        previousSymbolWasInLetter = false;
                    }
                }

            }
            if(previousSymbolWasInLetter) {
                mapForWords[newWord]++;
                counterOfAllWords++;
                newWord = "";
                previousSymbolWasInLetter = false;
            }
        }
    }

    void countingWords::sortingWordsAndWritingToOutputFile(){
        std::vector <std::pair<std::string,int>> vectorOfWords(mapForWords.begin(), mapForWords.end() );
        std::sort(vectorOfWords.begin(), vectorOfWords.end(), countingWords::comparatorForSort);
        auto it = vectorOfWords.begin();
        F_out << "Words, Frequency, Frequency %"<< std::endl;
        while(it != vectorOfWords.end()){
            F_out << it->first << ", " << it->second <<", "<< round((double)it->second/double(counterOfAllWords)*100)<<"%" << std::endl;
            it++;
        }
    }

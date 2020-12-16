#ifndef LAB4_CSVPARSER_H
#define LAB4_CSVPARSER_H

#include <iostream>
#include <fstream>
#include <tuple>
using namespace std;

///exit from recursion
template<size_t i, typename... Args>
typename enable_if<(i >= sizeof...(Args))>::type
printTuple(ostream &, const std::tuple<Args...> &){
    return;
}

///recursion typing of fields from tuple
template<size_t i, typename... Args>
typename enable_if<(i < sizeof...(Args))>::type
printTuple(ostream &os, const tuple<Args...> &tup) {
    if (i == 0) os << "#";
    os << get<i>(tup);
    if (i == 0) os << ". ";
    printTuple<i + 1>(os, tup);

}

///operator << for cout and tuple
template<typename... Args>
ostream &operator<<(ostream &os, const std::tuple<Args...> &tup) {
    printTuple<0>(os, tup);
    return os << "";
}

template<class ... Args>
class CSVParser {
private:
    ifstream &inputFile;
    int lengthOfInputFile = -1;
    int skipLines;
    char fieldSeparator = '"';
    char columnSeparator = ',';
    char lineSeparator = '\n';

    void resetInputFile(){
        inputFile.clear();
        inputFile.seekg(0, ios::beg);
    }

    int getLengthOfInputFile(){
        if(lengthOfInputFile == -1){
            resetInputFile();
            string line;
            lengthOfInputFile = 0;
            while(getline(inputFile, line)) lengthOfInputFile++;
            resetInputFile();
        }
        return lengthOfInputFile;
    }

    void getNewLine(ifstream &input, string &str) {
        str.clear();
        char c;
        while(input.get(c)){
            if(c == lineSeparator) break;
            str.push_back(c);
        }
    }

    class InputCSVIterator {
    private:
        friend class CSVParser;
        int lineNumber;
        ifstream &file;
        string buffer;
        CSVParser<Args...> &parent;
        bool EOFLineInFile = false;
        void jumpToNumberOfLine(int numberOfLine){
            for(int i = 0; i < numberOfLine; i++) {
                parent.getNewLine(file, buffer);
            }
        }

    public:
        InputCSVIterator(ifstream &stream, int skip, CSVParser<Args...> &parentClass) : parent(parentClass), file(stream) {
            parent.resetInputFile();
            lineNumber=skip+1;
            jumpToNumberOfLine(lineNumber);
            if(file.eof()) throw logic_error("Short file! Skip lines is equal with length file!");
            parent.resetInputFile();
        }

        InputCSVIterator operator++() {
            parent.resetInputFile();
            jumpToNumberOfLine(lineNumber);
            if(!EOFLineInFile){
                lineNumber++;
                parent.getNewLine(file, buffer);
                if(file.eof()){
                    EOFLineInFile = true;
                    buffer = "";
                }
            }
            else{
                buffer = "";
            }
            return *this;
        }

        bool operator==(const InputCSVIterator &secondIterator) const {
            return this->EOFLineInFile == secondIterator.EOFLineInFile && this->lineNumber == secondIterator.lineNumber && this->buffer == secondIterator.buffer;
        }

        bool operator!=(const InputCSVIterator &secondIterator) const {
            return !(*this == secondIterator);
        }

        tuple<Args...> operator*(){
            return parent.parseCurrentLine(lineNumber, buffer);
        }
    };
public:
    explicit CSVParser(ifstream &file, int skipNumber) : inputFile(file), skipLines(skipNumber){
        if(!inputFile.is_open()) throw invalid_argument("Can't open file");
        if(skipLines < 0) throw logic_error("Skip Lines < 0");
        if(skipLines > getLengthOfInputFile()) throw logic_error("Skip Lines > file length");
    }

    void changeSeparators(char field, char column, char line){
        fieldSeparator = field;
        columnSeparator = column;
        lineSeparator = line;
    }

    InputCSVIterator begin(){
        InputCSVIterator a(inputFile, skipLines, *this);
        return a;
    }

    InputCSVIterator end(){
        InputCSVIterator a(inputFile, 0, *this); //make new iterator
        a.EOFLineInFile = true;
        a.buffer = "";
        a.lineNumber = getLengthOfInputFile()+1;
        return a;
    }

    tuple<int, string> parseCurrentLine(int numberOfLine, string &currentLine){
        if(currentLine.empty()) throw invalid_argument("There aren't fields in line number "+to_string(numberOfLine)+"!");
        string parsedString;
        bool openQuotation = false;
        bool newColumn = false;
        for(auto sym : currentLine){
            if(newColumn){
                newColumn = false;
            }
            else{
                if(sym==fieldSeparator){
                    if (openQuotation) openQuotation = false;
                    else openQuotation = true;
                }
                else if(sym==columnSeparator){
                    newColumn = true;
                    if(!openQuotation) parsedString+="  |  ";
                    else parsedString+=sym;
                }
                else parsedString+=sym;
            }

        }
        return make_tuple(numberOfLine,parsedString);
    }
};
#endif //LAB4_CSVPARSER_H

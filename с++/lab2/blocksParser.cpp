#include "blocksParser.h"

shared_ptr<worker> initializerOfNewBlock(ifstream &fin){
    string inputString;
    fin>>inputString;
    if(inputString!="=") throw invalid_argument("Parser couldn't find '='-symbol in file with blocks!");
    fin>>inputString;
    shared_ptr<worker> newBlock;
    if(inputString=="dump"){
        string nameOfFile;
        fin>>nameOfFile;
        newBlock = make_shared<dumpBlock>(nameOfFile);
        return newBlock;
    }else if(inputString=="grep"){
        string word;
        fin>>word;
        newBlock = make_shared<grepBlock>(word);
        return newBlock;
    }else if(inputString=="readfile"){
        string nameOfFile;
        fin>>nameOfFile;
        newBlock = make_shared<readFileBlock>(nameOfFile);
        return newBlock;
    }
    else if(inputString=="replace"){
        string oldWord, newWord;
        fin>>oldWord>>newWord;
        newBlock = make_shared<replaceBlock>(oldWord, newWord);
        return newBlock;
    }else if(inputString=="sort"){
        newBlock = make_shared<sortBlock>();
        return newBlock;
    }else if(inputString=="writefile"){
        string nameOfFile;
        fin>>nameOfFile;
        newBlock = make_shared<writeFileBlock>(nameOfFile);
        return newBlock;
    }
    else{
        throw invalid_argument("Parser couldn't find correct name of block in file with blocks!");
    }
}

bool parseBlocks(map<unsigned int, shared_ptr<worker>> &blocks, ifstream& fin){
    if(fin.eof()) throw invalid_argument("Empty structure file!");
    string inputString;
    uint indexOfBlock;
    fin>>inputString;
    if(inputString!="desc") throw invalid_argument("Parser couldn't find 'desc'-string in file!");
    fin>>inputString;
    if(fin.eof()) return false;
    while(inputString!="csed"){
        indexOfBlock = stoi(inputString);
        if(blocks.count(indexOfBlock)) throw invalid_argument("Parser found double-initialized block in file with blocks!");
        else blocks[indexOfBlock]=initializerOfNewBlock(fin);
        fin>>inputString;
        if(fin.eof()) return false;
    }
    return true;
}

bool parseQueue(vector<uint> &queueOfBlocks,map<unsigned int, shared_ptr<worker>> &blocks, ifstream &fin){
    if(fin.eof()) throw invalid_argument("Empty structure file!");
    string inputString;
    uint indexOfBlock;
    fin>>inputString;
    if(fin.eof()) return false;
    while(true){
        indexOfBlock = stoi(inputString);
        if(!blocks.count(indexOfBlock)) throw invalid_argument("Parser couldn't find number of initialized block from block-queue!");
        queueOfBlocks.push_back(indexOfBlock);
        fin>>inputString;
        if(fin.eof()) break;
        if(inputString!="->") throw invalid_argument("Parser found unknown symbol in the block-queue!");
        fin>>inputString;
    }
    return true;
}
workflow parserOfStructureFile(const string& structureFile) {
    ifstream fin(structureFile);
    if(!fin.is_open()) throw invalid_argument("Can not open the structure file with program blocks!");
    map<unsigned int, shared_ptr<worker>> blocks;
    vector<uint> queueOfBlocks;
    if(!parseBlocks(blocks,fin)) throw invalid_argument("Parsing blocks failed!");
    if(!parseQueue(queueOfBlocks, blocks,fin)) throw invalid_argument("Parsing queue failed!");
    if(!dynamic_pointer_cast<readFileBlock>(blocks[queueOfBlocks[0]])) throw invalid_argument("First block in queue isn't 'readfile'!");
    if(!dynamic_pointer_cast<writeFileBlock>(blocks[queueOfBlocks.back()])) throw invalid_argument("Last block in queue isn't 'writefile'!");
    fin.close();
    return workflow(blocks,queueOfBlocks);
}

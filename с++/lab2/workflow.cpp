#include "workflow.h"

void workflow::execute() {
    vector<string> input;
    vector<string> output;
    bool inputData = false;
    for(auto  i : queueOfBlocks){
        inputData=blocks[i]->execute(input, output, inputData);
        input = output;
    }
}

#ifndef LAB2_WORKFLOW_H
#define LAB2_WORKFLOW_H
#include "worker.h"

class workflow {
private:
    vector<uint>queueOfBlocks;
    map<uint,shared_ptr<worker>> blocks;
public:
    workflow(map<unsigned int, shared_ptr<worker>> &inputBlocks, vector<uint> &inputQueueOfBlocks){
        blocks=move(inputBlocks);
        queueOfBlocks=move(inputQueueOfBlocks);
    }
    ~workflow(){
        blocks.clear();
        queueOfBlocks.clear();
    }
    void execute();
};


#endif //LAB2_WORKFLOW_H

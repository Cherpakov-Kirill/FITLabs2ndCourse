#include "blocksParser.h"

int main(int argc, char** argv) {
    if(argc<2) throw invalid_argument("Wrong number of arguments from console!");
    string programStructureFile = argv[1];
    workflow conveyor = parserOfStructureFile(programStructureFile);
    conveyor.execute();
    return 0;
}

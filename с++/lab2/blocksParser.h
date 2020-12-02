#ifndef LAB2_BLOCKSPARSER_H
#define LAB2_BLOCKSPARSER_H
#include "dumpBlock.h"
#include "grepBlock.h"
#include "readFileBlock.h"
#include "replaceBlock.h"
#include "sortBlock.h"
#include "worker.h"
#include "workflow.h"
#include "writeFileBlock.h"

workflow parserOfStructureFile(const string& structureFile);

#endif //LAB2_BLOCKSPARSER_H

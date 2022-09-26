#include "log.h"
#include "debug.h"

#include "fileIndex.h"

//TODO: Tests

FileIndex::FileIndex(FS* fs){
    FUN();
    DEBUG_EX("FileIndex::FileIndex()");

    _fs = fs;
}

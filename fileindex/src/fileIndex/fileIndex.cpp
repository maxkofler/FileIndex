#include "log.h"
#include "debug.h"

#include "fileIndex.h"

//TODO: Tests

FileIndex::FileIndex(FS* fs) : _fs(fs){
    FUN();
    DEBUG_EX("FileIndex::FileIndex()");
}

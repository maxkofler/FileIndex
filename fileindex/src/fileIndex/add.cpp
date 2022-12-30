#include "log.h"
#include "debug.h"

#include "fileIndex.h"

bool FileIndex::add(std::string& path){
    FUN();

    return _fs->add(path);
}

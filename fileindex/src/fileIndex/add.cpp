#include "log.h"
#include "debug.h"

#include "fileIndex.h"

size_t FileIndex::add(std::string& name, fs_entry entry){
    FUN();

    return _fs->add(name, entry);
}

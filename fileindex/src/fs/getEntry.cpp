#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests

fs_entry* FS::getEntry(size_t id){
    FUN();
    DEBUG_EX("FS::getEntry()");

    if (id > _entries.size()-1)
        return nullptr;

    return &_entries._data[id];
}

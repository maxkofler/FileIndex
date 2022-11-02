#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests

fs_entry* FS::getEntry(size_t id){
    FUN();
    DEBUG_EX("FS::getEntry()");

    return _db->getEntry(id);
}

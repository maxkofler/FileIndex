#include "log.h"
#include "debug.h"

#include "fs.h"
#include "crate.h"

//TODO: Tests

size_t FS::add(const std::string& name, const fs_entry& entry){
    FUN();
    DEBUG_EX("FS::add()");

    auto id = _db->add(name, entry);
    _db->getEntry(_db->getEntriesCount()-1)->nameID = id;
    return id;
}

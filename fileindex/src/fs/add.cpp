#include "log.h"
#include "debug.h"

#include "fs.h"
#include "crate.h"

//TODO: Tests

size_t FS::add(const std::string& name, const fs_entry& oEntry){
    FUN();
    DEBUG_EX("FS::add()");

    fs_entry entry = oEntry;

    entry.nameID =  _db->getEntriesCount();

    LOGMEM("[FS][add] Added entry " + fs_entry_str(entry) + ": " + name);
    return _db->add(name, entry);
}

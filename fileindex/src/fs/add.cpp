#include "log.h"
#include "debug.h"

#include "fs.h"
#include "crate.h"

//TODO: Tests

size_t FS::add(const std::string& name, const fs_entry& entry){
    FUN();
    DEBUG_EX("FS::add()");

    //Add the new entry
    _entries.add(entry);
    _entries._data[_entries.lastID()].nameID = _db->add(name, (void*)(_entries.lastID()));

    return _entries.lastID();
}

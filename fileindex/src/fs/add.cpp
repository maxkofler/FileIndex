#include "log.h"
#include "debug.h"

#include "fs.h"
#include "crate.h"

//TODO: Tests

size_t FS::add(const std::string& name, const fs_entry& entry){
    FUN();
    DEBUG_EX("FS::add()");

    while(_size_entries < (_count_entries+1))
        expand();

    #warning This implementation is flawed! The crates should be stored in an array for size_t entries in the DB
    //Add the new entry
    _entries[_count_entries] = entry;
    _count_entries++;

    if (_useDirtyDB){
        _dirtyDB->add(name, (void*)(_count_entries-1));
    } else {
        crate_s<size_t>* newCrate = crate_new<size_t>();
        crate_add<size_t>(newCrate, _count_entries-1);
        _db->add(name, newCrate);
    }

    return _count_entries-1;
}

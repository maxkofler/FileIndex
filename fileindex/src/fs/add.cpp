#include "log.h"
#include "debug.h"

#include "fs.h"
#include "crate.h"

//TODO: Tests

size_t FS::add(const std::string& name, const fs_entry& entry){
    FUN();
    DEBUG_EX("FS::add()");

    #warning This implementation is flawed! The crates should be stored in an array for size_t entries in the DB
    //Add the new entry
    _entries.add(entry);

    if (_useDirtyDB){
        //_dirtyDB->add(name, (void*)(_entries.lastID()));
    } else {
        /*
        crate_s<size_t> newCrate;
        newCrate.data = nullptr;
        newCrate.size = 0;
        
        _crates.add(newCrate);

        crate_add<size_t>(&_crates._data[_entries.lastID()], _entries.lastID());

        _db->add(name, (void*)(_crates.lastID()));
        */
    }

    return _entries._size-1;
}

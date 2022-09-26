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

    if (_useDirtyDB){
        _entries._data[_entries.lastID()].nameID = _db->add(name, (void*)(_entries.lastID()));
    } else {
        crate_s<size_t> newCrate;
        newCrate.data = nullptr;
        newCrate.size = 0;
        
        _crates.add(newCrate);

        _crates._data[_crates.lastID()].size = 0;
        _crates._data[_crates.lastID()].data = nullptr;
        crate_add<size_t>(&_crates._data[_crates.lastID()], _entries.lastID());

        _entries._data[_entries.lastID()].nameID = _db->add(name, (void*)_crates.lastID());
    }

    return _entries.lastID();
}

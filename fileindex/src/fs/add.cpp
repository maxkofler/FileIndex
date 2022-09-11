#include "log.h"
#include "debug.h"

#include "fs.h"
#include "fsCrate.h"
#include "crate.h"

//TODO: Tests

void FS::add(const std::string& name, const fs_entry& entry){
    FUN();
    DEBUG_EX("FS::add()");

    while(_size_entries < (_count_entries+1))
        expand();

    if (_useDirtyDB){
        _dirtyDB->add(name, (void*)_count_entries);
    } else {
        LOGUE("[FS][add] Unimplemented path!");
        //fs_crate* crate = new fs_crate;
        //FSCrate_add(crate, );
        //_db.add(name, crate);
    }

    _entries[_count_entries] = entry;

    _count_entries++;
}

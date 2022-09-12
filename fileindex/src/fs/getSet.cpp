#include "log.h"
#include "debug.h"

#include "fs.h"

NamesDB* FS::getDB(){
    return _db;
}

bool FS::getUseDirtyDB(){
    return _useDirtyDB;
}

NamesDB* FS::getDirtyDB(){
    if (getUseDirtyDB())
        return _dirtyDB;
    else
        return nullptr;
}

crate_s<size_t>* FS::getCrate(size_t id){
    if (id >= _crates.size())
        return nullptr;

    return &_crates._data[id];
}

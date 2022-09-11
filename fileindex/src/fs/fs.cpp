#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests

FS::FS(NamesDB* db, bool useDirtyDB, size_t chunkSize) : _useDirtyDB(useDirtyDB), _chunkSize(chunkSize){
    FUN();

    if (db == nullptr){
        db = new NamesDB("fs_db");
    }

    _db = db;

    if (_useDirtyDB)
        _dirtyDB = new NamesDB("fs_dirty_db");
}

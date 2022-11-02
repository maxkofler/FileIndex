#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests

FS::FS(NamesDB<fs_entry>* db, size_t chunkSize) : _chunkSize(chunkSize){
    FUN();

    if (db == nullptr){
        db = new NamesDB<fs_entry>("fs_db");
    }

    _db = db;

    if (_db->getEntriesCount() == 0){
        fs_dir dir;
        dir.parentID = 0;
        add(std::string("fs"), dir);
    }
}

FS::~FS(){
    FUN();

    LOGMEM("[FS] Cleaning up instance...");
}

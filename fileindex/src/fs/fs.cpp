#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests

FS::FS(SQL& sql) : _sql(sql){
    FUN();

    createTables();
}

FS::~FS(){
    FUN();

    LOGMEM("[FS] Cleaning up instance...");
}

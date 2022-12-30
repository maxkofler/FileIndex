#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests

FS::FS() : _sql("fs.sql"){
    FUN();

    {//Create the table if not existing
        std::string cmd = "CREATE TABLE IF NOT EXISTS entries (";
        cmd += "id INTEGER PRIMARY KEY AUTOINCREMENT,";
        cmd += "path TEXT UNIQUE NOT NULL);";
        if (!_sql.exec(cmd)){
            LOGUE("SQL failed: " + _sql.getError());
        }
    }
}

FS::~FS(){
    FUN();

    LOGMEM("[FS] Cleaning up instance...");
}

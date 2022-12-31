#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests

FS::FS(SQL& sql) : _sql(sql){
    FUN();

    {//Enable foreign key support
        _sql.exec("PRAGMA foreign_keys = ON;");
    }

    {//Create the names table
        std::string cmd = "CREATE TABLE IF NOT EXISTS names (";
        cmd += "id INTEGER PRIMARY KEY AUTOINCREMENT,";
        cmd += "name TEXT UNIQUE NOT NULL";
        cmd += ");";
        if (_sql.exec(cmd).code){
            LOGUE("SQL failed: " + _sql.getError());
        }
    }

    {//Create the entries table if not existing
        std::string cmd = "CREATE TABLE IF NOT EXISTS entries (";
        cmd += "id INTEGER PRIMARY KEY AUTOINCREMENT,";
        cmd += "nameID INTEGER NOT NULL,";
        cmd += "parentID INTEGER NOT NULL,";
        cmd += "isDir BOOLEAN NOT NULL,";
        cmd += "FOREIGN KEY (nameID) REFERENCES names (id),";
        cmd += "FOREIGN KEY (parentID) REFERENCES entries (id),";
        cmd += "UNIQUE (nameID, parentID)";
        cmd += ");";
        if (_sql.exec(cmd).code){
            LOGUE("SQL failed: " + _sql.getError());
        }
    }
}

FS::~FS(){
    FUN();

    LOGMEM("[FS] Cleaning up instance...");
}

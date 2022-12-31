#include "log.h"
#include "debug.h"

#include "fs.h"
#include "crate.h"

//TODO: Tests
bool FS::add(const std::string& path){
    FUN();
    DEBUG_EX("FS::add()");

    std::string sql = "INSERT INTO entries (path) VALUES (\"" + path + "\");";
    if (_sql.exec(sql).code){
        LOGUE("[SQL Error] '" + _sql.getError() + "' when adding " + path);
        return false;
    }

    LOGMEM("[FS][add] Added entry " + path);
    return true;
}

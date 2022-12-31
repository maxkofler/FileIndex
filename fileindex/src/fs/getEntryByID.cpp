#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests

fs_entry FS::getEntryByID(uint64_t id){
    FUN();
    fs_entry e;
    e.id = 0;

    {
        std::string cmd = "SELECT isDir, nameID, parentID FROM entries WHERE id = " + std::to_string(id) + ";";
        SQL_res res = _sql.exec(cmd);

        if (res.code){
            LOGUE("[SQL Error] '" + _sql.getError() + "' when looking up entry id " + std::to_string(id));
            return e;
        }

        //The id is unique
        std::deque<std::string> entry = res.result.at(0);

        e = fs_entry_parse(entry.at(0), std::to_string(id), "no name", entry.at(1), entry.at(2));
    }

    {
        std::string cmd = "SELECT name FROM names WHERE id = " + std::to_string(e.nameID) + ";";
        SQL_res res = _sql.exec(cmd);

        if (res.code){
            LOGUE("[SQL Error] '" + _sql.getError() + "' when looking up name by id " + std::to_string(e.nameID));
            return e;
        }

        //The nameid is unique
        e.name = res.result.at(0).at(0);
    }

    LOGMEM("[FS] Resolved entry " + fs_entry_str(e) + " from ID=" + std::to_string(id));

    return e;
}

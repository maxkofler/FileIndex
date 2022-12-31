#include "log.h"
#include "debug.h"

#include "fs.h"
#include "crate.h"

//TODO: Tests
bool FS::add(fs_entry& entry){
    FUN();
    DEBUG_EX("FS::add()");

    {   //Create the name
        std::string cmd = "INSERT OR IGNORE INTO names (name) VALUES ('" + entry.name + "');";
        cmd += "SELECT id FROM names WHERE name = '" + entry.name + "';";

        SQL_res res = _sql.exec(cmd);
        if (res.code){
            LOGUE("[SQL Error] '" + _sql.getError() + "' when adding name " + entry.name);
            return false;
        }

        if (res.result.size() == 0){
            //LOGUE("[FS] ")
        }
        entry.nameID = std::stoi(res.result.at(0).at(0));
    }

    {   //Insert the entity
        std::string cmd = "INSERT OR IGNORE INTO entries (nameID, parentID, isDir) VALUES (";
        cmd += std::to_string(entry.nameID) + ",";
        cmd += std::to_string(entry.parentID) + ",";
        cmd += std::to_string(entry.isDir);
        cmd += ");";
        cmd += "SELECT id FROM entries WHERE nameID = " + std::to_string(entry.nameID) + " AND parentID = " + std::to_string(entry.parentID) + ";";


        SQL_res res = _sql.exec(cmd);
        if (res.code){
            LOGUE("[SQL Error] '" + _sql.getError() + "' when adding entry " + fs_entry_str(entry));
            return false;
        }

        entry.id = std::stoi(res.result[0][0]);
    }

    return true;
}

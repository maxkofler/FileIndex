#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests
std::deque<fs_entry> FS::search(const std::string& search, bool matchCase, bool exact){
    FUN();
    DEBUG_EX("FS::search()");

    std::deque<fs_entry> ret;
    std::string cmd;

    //Check for matching case
    if(matchCase)
        cmd += "PRAGMA case_sensitive_like=ON;";
    else
        cmd += "PRAGMA case_sensitive_like=OFF;";

    //Construct the core command
    cmd += "SELECT m.name, e.isDir, e.id, e.nameID, e.parentID ";
    cmd += "FROM entries e, names m ";
    cmd += "WHERE e.nameID = m.id AND ";

    //And check if searching exactly
    if (exact)
        cmd += "m.name LIKE ('" + search + "');";
    else
        cmd += "m.name LIKE ('%" + search + "%');";

    //Execute the command    
    SQL_res res = _sql.exec(cmd);

    //Check the return code
    if (res.code){
        LOGUE("[SQL Error] '" + _sql.getError() + "' when searching " +
            (exact ? "EXACTLY " : "") +
            (matchCase ? "CASE MATCHED " : "") +
            "for " + search
            );
        return ret;
    }

    //Transform the results
    for (std::deque<std::string> entry : res.result){
        ret.push_back(fs_entry_parse(entry.at(1), entry.at(2), entry.at(0), entry.at(3), entry.at(4)));
    }

    return ret;
}

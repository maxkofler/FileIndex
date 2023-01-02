#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests

std::deque<fs_entry> FS::getPath(fs_entry& entry){
    FUN();

    std::deque<fs_entry> ret;

    std::string cmd;
    cmd += "WITH parent AS(";
    cmd += " SELECT *";
    cmd += " FROM entries WHERE id = " + std::to_string(entry.id);
    cmd += " UNION ALL";
    cmd += " SELECT entries.*";
    cmd += " FROM entries JOIN parent ON entries.id = parent.parentID)";
    cmd += " SELECT p.id, p.nameID, p.parentID, p.isDir, n.name";
    cmd += " FROM parent p, names n WHERE p.nameID = n.id;";

    SQL_res res = _sql.exec(cmd);
    if (res.code){
        LOGUE("[SQL Error] " + _sql.getError() + " when looking up path of " + fs_entry_str(entry));
    }

    for (std::deque<std::string> line : res.result){
        ret.push_front(fs_entry_parse(line.at(3), line.at(0), line.at(4), line.at(1), line.at(2)));
    }

    return ret;
}

std::string FS::getPathString(fs_entry& entry){
    FUN();

    std::string ret;
    std::deque<fs_entry> entries = getPath(entry);

    for (fs_entry e : entries)
        ret += e.name + "/";

    //Remove trailing '/'
    if (ret.length() > 0)
        ret = ret.replace(ret.length()-1, 1, "");

    return ret;
}

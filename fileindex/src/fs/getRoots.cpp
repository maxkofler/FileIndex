#include "log.h"
#include "debug.h"

#include "fs.h"
#include "crate.h"

std::deque<fs_entry> FS::getRoots(){
	FUN();
	std::deque<fs_entry> ret;

	std::string cmd;
	cmd += " SELECT e.id, e.nameID, e.parentID, e.isDir, n.name";
    cmd += " FROM entries e, names n WHERE e.nameID = n.id AND e.parentID = 0;";

	SQL_res res = _sql.exec(cmd);
    if (res.code){
        LOGUE("[SQL Error] " + _sql.getError() + " when getting roots of FS");
    }

    for (std::deque<std::string> line : res.result){
        ret.push_front(fs_entry_parse(line.at(3), line.at(0), line.at(4), line.at(1), line.at(2)));
    }

	return ret;
}

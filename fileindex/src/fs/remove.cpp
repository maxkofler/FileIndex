#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests
void FS::remove(const fsentry_s& entry){
	FUN();
	DEBUG_EX("FS::remove()");

	std::string cmd;
	cmd += "WITH children AS(";
    cmd += " SELECT id FROM entries WHERE id = ";
	cmd += std::to_string(entry.id);
    cmd += " UNION ALL SELECT entries.id";
	cmd += " FROM entries JOIN children  ON entries.ParentId = children.id)";
	cmd += " DELETE FROM entries WHERE id IN children;";

	//Execute the command
    SQL_res res = _sql.exec(cmd);

    //Check the return code
    if (res.code)
        LOGUE("[SQL Error] '" + _sql.getError() + "' when deleting entry " + fs_entry_str(entry));
}

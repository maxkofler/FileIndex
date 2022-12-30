
#include <sqlite3.h>

#include "log.h"
#include "sql.h"

bool SQL::exec(std::string cmd){
	FUN();

	LOGMEM("[SQL] Executing: '" + cmd + "'");

	if (_db == nullptr){
		LOGUE("[SQL] Tried to exec in faulty (nullptr) db!");
		return false;
	}

	int res = sqlite3_exec(_db, cmd.c_str(), NULL, NULL, NULL);

	return res == SQLITE_OK;
}

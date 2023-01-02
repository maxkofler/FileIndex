
#include "log.h"

#include <sqlite3.h>
#include "sql.h"

bool SQL::save(std::string outFile){
	FUN();

	sqlite3* outDB;

	//Open the backup connection
	int res = sqlite3_open(outFile.c_str(), &outDB);
	if (res){
		LOGUE("[SQL] Failed to connect to backup SQLite " + _sqlFile + ": " + getError());
		sqlite3_free(outDB);
		return false;
	}

	//Lock the exec call while creating the backup
	_m_exec.lock();

	sqlite3_backup* bu = sqlite3_backup_init(outDB, "main", _db, "main");
	if (bu){
		sqlite3_backup_step(bu, -1);
		sqlite3_backup_finish(bu);
	} else {
		LOGUE("[SQL] Failed to create backup: " + std::string(sqlite3_errmsg(_db)));
	}

	//Unlock the exec call
	_m_exec.unlock();

	//Close the backup database
	sqlite3_close(outDB);

	return bu != nullptr;
}

bool SQL::load(std::string inFile){
	FUN();

	_m_exec.lock();

	//Close the old database file
	if (_db != nullptr){
		sqlite3_close(_db);
		_db = nullptr;
	}

	_sqlFile = inFile;

	//Open the new connection
	int res = sqlite3_open(_sqlFile.c_str(), &_db);
	if (res){
		LOGUE("[SQL] Failed to connect to SQLite " + _sqlFile + ": " + getError());
		sqlite3_free(_db);
		_db = nullptr;
	}

	//Unlock the exec call
	_m_exec.unlock();

	return _db != nullptr;
}

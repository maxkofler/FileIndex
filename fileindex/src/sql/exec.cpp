
#include <sqlite3.h>

#include "log.h"
#include "sql.h"

int SQL::s_sqlite3_callback(void* data, int argc, char **argv, char **azColName){
	FUN();

	return ((SQL*)data)->sqlite3_callback(argc, argv, azColName);
}

int SQL::sqlite3_callback(int argc, char **argv, char **azColName){
	FUN();

	std::deque<std::string> curRes;

	for (int i = 0; i < argc; i++){
		curRes.push_back(std::string(argv[i] ? argv[i] : "NULL"));
	}

	_sql_res.push_back(curRes);

	return 0;
}

SQL_res SQL::exec(std::string cmd){
	FUN();
	SQL_res res;

	LOGMEM("[SQL] Executing: '" + cmd + "'");

	if (_db == nullptr){
		LOGUE("[SQL] Tried to exec in faulty (nullptr) db!");
		res.code = -1;
		return res;
	}

	_sql_res.clear();
	res.code = sqlite3_exec(_db, cmd.c_str(), s_sqlite3_callback, this, NULL);
	res.result = _sql_res;

	return res;
}

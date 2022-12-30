
#include <sqlite3.h>

#include "log.h"
#include "sql.h"

SQL::SQL(std::string sqlFile) : _sqlFile(sqlFile){
	FUN();

	int res = sqlite3_open(sqlFile.c_str(), &_db);

	if (res){
		LOGUE("[SQL] Failed to connect to SQL file " + sqlFile + ": " + getError());
		sqlite3_free(_db);
		_db = nullptr;
		return;
	}
}

SQL::~SQL(){
	FUN();

	if (_db != nullptr){
		sqlite3_close(_db);
	}
}

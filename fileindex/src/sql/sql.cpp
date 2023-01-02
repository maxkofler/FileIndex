
#include <sqlite3.h>

#include "log.h"
#include "sql.h"

SQL::SQL(std::string sqlFile) : _sqlFile(sqlFile){
	FUN();

	if (sqlFile == ""){
		LOGI("[SQL] Creating memory database...");
		_sqlFile = ":memory:";
	}

	load(_sqlFile);
}

SQL::~SQL(){
	FUN();

	if (_db != nullptr){
		sqlite3_close(_db);
	}
}

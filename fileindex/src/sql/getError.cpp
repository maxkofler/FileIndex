
#include <sqlite3.h>

#include "log.h"
#include "sql.h"

std::string SQL::getError(){
	FUN();

	if (_db == nullptr){
		LOGUE("[SQL] Tried to get error of faulty (nullptr) db!");
		return "Database is nullptr!";
	}

	return std::string(sqlite3_errmsg(_db));
}

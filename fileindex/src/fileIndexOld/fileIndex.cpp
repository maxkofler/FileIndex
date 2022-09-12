#include "log.h"
#include "fileIndexOld.h"
#include "debug.h"

FileIndexOld::FileIndexOld(NamesDB* db){
	FUN();
	DEBUG_EX("FileIndex::FileIndex()");

	if (db == nullptr){
		LOGD("[FileIndex] No main database supplied, creating one...");
		_db = new NamesDB("main");
		_externalDB = false;
	} else {
		_db = db;
		_externalDB = true;
	}

	LOGMEM("[FileIndex] Creating dirty database...");
	_dirtyDB = new NamesDB("dirty");
}

FileIndexOld::~FileIndexOld(){
	FUN();

	if (!_externalDB){
		LOGD("[FileIndex] Deleting internal database");
		delete _db;
	}

	delete _dirtyDB;
}

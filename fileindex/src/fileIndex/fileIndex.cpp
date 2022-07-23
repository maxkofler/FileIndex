#include "log.h"
#include "fileIndex.h"
#include "debug.h"

FileIndex::FileIndex(NamesDB* db){
	FUN();
	DEBUG_EX("FileIndex::FileIndex()");

	if (db == nullptr){
		LOGD("[FileIndex] No database supplied, creating one...");
		_db = new NamesDB();
		_externalDB = false;
	} else {
		_db = db;
		_externalDB = true;
	}

	_dirtyDB = new NamesDB();
}

FileIndex::~FileIndex(){
	FUN();

	if (!_externalDB){
		LOGD("[FileIndex] Deleting internal database");
		delete _db;
	}

	delete _dirtyDB;
}

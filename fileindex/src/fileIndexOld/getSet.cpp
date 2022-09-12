#include "log.h"
#include "fileIndexOld.h"

NamesDB* FileIndexOld::getDB(){
	FUN();

	return _db;
}

size_t FileIndexOld::getSavedDuplicatesCount(){
	FUN();

	return _savedDuplicateNames;
}

size_t FileIndexOld::getIndexedEntriesCount(){
	FUN();

	return _indexedEntries;
}

#include "log.h"
#include "fileIndex.h"

NamesDB* FileIndex::getDB(){
	FUN();

	return _db;
}

size_t FileIndex::getSavedDuplicatesCount(){
	FUN();

	return _savedDuplicateNames;
}

size_t FileIndex::getIndexedEntriesCount(){
	FUN();

	return _indexedEntries;
}

#include "log.h"
#include "namesDB.h"

size_t NamesDB::getEntriesCount(){
	return _count_entries;
}

size_t NamesDB::getBytesUsed(){
	return _used_bytes;
}

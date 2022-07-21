#include "log.h"
#include "fileIndex.h"

NamesDB* FileIndex::getDB(){
	FUN();

	return _db;
}

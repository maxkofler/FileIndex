#include "log.h"
#include "fileIndex.h"

void FileIndex::cleanDB(){
	FUN();

	_db->clean();
}

void FileIndex::cleanDirtyDB(){
	FUN();

	_dirtyDB->clean();
}

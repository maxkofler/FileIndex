#include "log.h"
#include "fileIndexOld.h"

void FileIndexOld::cleanDB(){
	FUN();

	_db->clean();
}

void FileIndexOld::cleanDirtyDB(){
	FUN();

	_dirtyDB->clean();
}

#define FRIEND_FS_ENTRY
#include "log.h"
#include "directory.h"

void Directory::addEntry(FSEntry* entry){
	FUN();

	entry->_parent = this;
}

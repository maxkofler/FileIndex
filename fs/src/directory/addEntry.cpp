#define FRIEND_FS_ENTRY
#include "log.h"
#include "fs.h"
#include "directory.h"

void Directory::addEntry(FSEntry* entry){
	FUN();

	if (entry == nullptr)
		return;

	#ifdef DEBUG
	LOGMEM("Adding " + FS::getName(entry) + " to " + FS::getPathString(this));
	#endif

	_entries.push_back(entry);

	entry->_parent = this;
}

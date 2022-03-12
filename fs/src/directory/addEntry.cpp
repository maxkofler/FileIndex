#define FRIEND_FS_ENTRY
#include "log.h"
#include "directory.h"

void Directory::addEntry(FSEntry* entry){
	FUN();

	#ifdef DEBUG
	LOGMEM("Adding " + entry->getName() + " to " + getPathString());
	#endif

	if (entry == nullptr)
		return;

	_entries.push_back(entry);

	entry->_parent = this;
}

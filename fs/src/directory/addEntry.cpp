#define FRIEND_FS_ENTRY
#include "log.h"
#include "directory.h"

void Directory::addEntry(FSEntry* entry){
	FUN();

	if (entry == nullptr)
		return;

	#ifdef DEBUG
	LOGMEM("Adding " + entry->getName() + " to " + this->getPathString());
	#endif

	_entries.push_back(entry);

	entry->_parent = this;
}

#define FRIEND_FS_ENTRY
#include "log.h"
#include "fs.h"
#include "directory.h"

void Directory::addEntry(FSEntry* entry){
	FUN();

	if (entry == nullptr)
		return;

	_entries.push_back(entry);

	entry->_parent = this;
}

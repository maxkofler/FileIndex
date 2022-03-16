#define FRIEND_FS_ENTRY
#include "log.h"
#include "fs.h"

std::deque<FSEntry*> FS::getPath(FSEntry* entry){
	FUN();

	FSEntry* last = entry;
	
	std::deque<FSEntry*> res;

	if (entry->_parent != nullptr)
		res = FS::getPath(entry->_parent);
	
	res.push_back(entry);

	return res;
}

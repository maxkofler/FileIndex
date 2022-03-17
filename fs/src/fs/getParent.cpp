#define FRIEND_FS_ENTRY
#include "log.h"
#include "fs.h"

Directory* FS::getParent(FSEntry* entry){
	return (Directory*)(entry->_parent);
}

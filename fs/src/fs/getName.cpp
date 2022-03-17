#define FRIEND_FS_ENTRY
#include "log.h"
#include "fs.h"

std::string FS::getName(FSEntry* entry){
	return std::string(*entry->_name);
}

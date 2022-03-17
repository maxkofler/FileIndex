#define FRIEND_FS_ENTRY
#include "log.h"
#include "fs.h"

std::string* FS::getNamePtr(FSEntry* entry){
	return entry->_name;
}

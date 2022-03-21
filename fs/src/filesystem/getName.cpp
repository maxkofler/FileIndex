#define FRIEND_FS_ENTRY
#include "log.h"
#include "filesystem.h"

std::string Filesystem::getName(fs_name name){
	uint32_t index = name.index;

	if (index > _cache_names->size() || index < 0)
		return "Index " + std::to_string(index) + " out of range";

	return std::string(_cache_names->at(index)->name);
}

std::string Filesystem::getName(FSEntry* entry){
	return getName(entry->_name);
}

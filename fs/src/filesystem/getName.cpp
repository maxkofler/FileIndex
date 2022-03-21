#define FRIEND_FS_ENTRY
#include "log.h"
#include "filesystem.h"

std::string Filesystem::getName(fs_name name){
	uint32_t index = name.index;

	fs_name_entry* entry = getNamePtr(name);

	if (entry == nullptr)
		return "Index " + std::to_string(index) + " out of range";

	return std::string(entry->name);
}

std::string Filesystem::getName(FSEntry* entry){
	return getName(entry->_name);
}

fs_name_entry* Filesystem::getNamePtr(fs_name name){
	if (name.index > _cache_names->size() || name.index < 0)
		return nullptr;

	return _cache_names->at(name.index);
}

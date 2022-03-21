#include "log.h"
#include "filesystem.h"

fs_name Filesystem::createName(std::string nameContent){
	FUN();

	_namesRequested++;

	//Allocate the new memory
	fs_name_entry* newName = new fs_name_entry;
	newName->len_name = nameContent.size();
	newName->name = new char[newName->len_name+1];
	newName->entries = new FSEntryList(false, 10);

	//Copy the name content
	std::strcpy(newName->name, nameContent.c_str());

	//Add the entry
	_cache_names->push_back(newName);

	LOGD("Created new name \"" + std::string(newName->name) + "\"");

	//Return the entry handle
	fs_name handle;
	handle.index = _cache_names->size()-1;
	return handle;

	//TODO: reenable checking for duplicates
	/*
	for (fs_name* name : *_cache_names){
		if (*name == nameContent){
			_duplicateNamesSaved++;
			return name;
		}
	}
	*/

}

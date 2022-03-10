#include "log.h"
#include "fs_entry.h"

std::string* FSEntry::getNamePtr(){
	return _name;
}

std::string FSEntry::getName(){
	if (_name == nullptr)
		return std::string("");
	else
		return std::string(*_name);
}

FSEntry* FSEntry::getParent(){
	return _parent;
}

std::string FSEntry::getPathString(){
	auto paths = getParents();
	std::string path;

	for(FSEntry* entry : paths)
		path += '/' + entry->getName();

	if (type() == FS::ENTRY_DIRECTORY)
		path += '/';

	return path;
}

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
	std::string path;
	auto parents = getParents();

	if (parents.size() > 0){
		path += parents[0]->getName();

		for (int i = 1; i < parents.size(); i++)
			path += '/' + parents[i]->getName();
	}

	if (type() == FS::ENTRY_DIRECTORY)
		path += '/';

	return path;
}

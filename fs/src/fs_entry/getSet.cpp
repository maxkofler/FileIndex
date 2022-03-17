#include "log.h"
#include "fs.h"
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

#include "log.h"
#include "fs_entry.h"

FSEntry::FSEntry(std::string* name, bool owns) : _name(name), _ownsName(owns){
	FUN();

	if (_ownsName)
		LOGMEM("Gained ownership of name \"" + getName() + "\"");
}

FSEntry::~FSEntry(){
	FUN();

	if (_name != nullptr){
		if (_ownsName){
			LOGMEM("Removing memory of name \"" + getName() + "\"");
			delete _name;
			_name = nullptr;
		}
	}
}
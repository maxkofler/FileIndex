#include "log.h"
#include "fs_entry.h"

FSEntry::FSEntry(std::string* name, bool owns) : _name(name), _ownsName(owns){
	FUN();
}

FSEntry::~FSEntry(){
	FUN();

	if (_name != nullptr){
		if (_ownsName){
			delete _name;
			_name = nullptr;
		}
	}
}
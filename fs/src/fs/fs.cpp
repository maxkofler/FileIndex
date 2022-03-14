#include "log.h"
#include "fs.h"

FS::FS(std::string root){
	FUN();

	_owns_names = true;
	_names = new std::vector<std::string>();

	_names->push_back(root);
	_root = new Directory(&(_names->back()));
}

FS::~FS(){
	FUN();

	if (_owns_names && _names != nullptr)
		delete _names;

	for (FSEntry* entry : _entries)
		if (entry != nullptr)
			delete entry;
}

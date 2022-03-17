#include "log.h"
#include "fs.h"
#include "filesystem.h"

Filesystem::Filesystem(std::string root){
	FUN();

	_owns_names = true;
	_names = new std::vector<std::string*>();

	_names->push_back(new std::string(root));
	_root = new Directory(_names->back());

	LOGI("Created new FS with root " + FS::getPathString(_root));
}

Filesystem::~Filesystem(){
	FUN();

	if (_owns_names && _names != nullptr)
		for (std::string* name : *_names)
			delete name;
		delete _names;

	for (FSEntry* entry : _entries)
		if (entry != nullptr)
			delete entry;
}

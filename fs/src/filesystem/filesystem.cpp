#include "log.h"
#include "fs.h"
#include "filesystem.h"

Filesystem::Filesystem(std::string root){
	FUN();

	_cache_names = new std::vector<std::string*>();
	_cache_entries = new std::deque<FSEntry*>();

	_cache_names->push_back(new std::string(root));
	_root = new Directory(_cache_names->back());

	LOGI("Created new FS with root " + FS::getPathString(_root));
}

Filesystem::~Filesystem(){
	FUN();

	if (_cache_names != nullptr){
		for (std::string* name : *_cache_names)
            if (name != nullptr)
                delete name;
		delete _cache_names;
	}

    if (_cache_entries != nullptr){
        for (FSEntry* entry : *_cache_entries)
            if (entry != nullptr)
                delete entry;
        delete _cache_entries;
    }
}

#include "log.h"
#include "fs.h"
#include "filesystem.h"

Filesystem::Filesystem(std::string root){
	FUN();

	_cache_names = new std::vector<fs_name_entry*>();
	_cache_entries = new std::deque<FSEntry*>();

	fs_name rootName = createName(root);
	_root = new Directory(rootName);

	LOGI("Created new FS with root " + FS::getPathString(_root));
}

Filesystem::~Filesystem(){
	FUN();

	//TODO: free memory of string
	if (_cache_names != nullptr){
		for (fs_name_entry* name : *_cache_names)
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

#include "log.h"
#include "directory.h"

FS::entry_type Directory::type(){
	return FS::ENTRY_DIRECTORY;
}

std::vector<FSEntry*>& Directory::getEntries(){
	return _entries;
}

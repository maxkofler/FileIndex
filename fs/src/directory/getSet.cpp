#include "log.h"
#include "directory.h"

FS::entry_type Directory::type(){
	return FS::ENTRY_DIRECTORY;
}

std::deque<FSEntry*>& Directory::getEntries(){
	return _entries;
}

std::deque<FSEntry*> Directory::getRecursiveEntries(){
	FUN();
	std::deque<FSEntry*> foundEntries;

	for (FSEntry* entry : _entries){
		
		if (entry == nullptr)
			continue;

		foundEntries.push_back(entry);

		if (entry->type() == FS::ENTRY_DIRECTORY){
			auto res = ((Directory*) entry)->getRecursiveEntries();

			foundEntries.insert(foundEntries.end(), res.begin(), res.end());
		}
			
	}

	return foundEntries;
}

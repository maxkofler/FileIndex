#include "log.h"
#include "fs_entry.h"

std::vector<FSEntry*> FSEntry::getParents(){
	FUN();

	std::vector<FSEntry*> entries;
	
	if (_parent != nullptr)
		entries = _parent->getParents();

	entries.push_back(this);

	return entries;
}

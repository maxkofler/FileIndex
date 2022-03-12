#include "log.h"
#include "fs_entry.h"

std::deque<FSEntry*> FSEntry::getParents(){
	FUN();

	std::deque<FSEntry*> entries;
	
	if (_parent != nullptr)
		entries = _parent->getParents();

	entries.push_back(this);

	return entries;
}

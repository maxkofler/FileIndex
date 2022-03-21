#include "log.h"
#include "fs_entry_list.h"

void FSEntryList::reallocate(size_t space){
	FUN();
    LOGD("Reallocating " + std::to_string(space) + " more entries...");
    
	size_t newAllocatedCount = _entries_allocated + space;

	FSEntry** newMem = new FSEntry*[newAllocatedCount];

	for (size_t i = 0; i < _entries_used; i++){
		newMem[i] = _entries[i];
	}

	//Delete the old array
	delete _entries;

	_entries = newMem;
	_entries_allocated = newAllocatedCount;
}

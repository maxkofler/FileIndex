#include "log.h"
#include "fs_entry_list.h"

void FSEntryList::addEntry(FSEntry* entry){
	FUN();

	if (_entries_used >= _entries_allocated){
		reallocate(1);
	}

	_entries[_entries_used] = entry;
	_entries_used++;
}

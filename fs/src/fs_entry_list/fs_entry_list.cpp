#include "log.h"
#include "fs_entry_list.h"

FSEntryList::FSEntryList(bool managesMem, size_t preallocate) : _managesEntries(managesMem){
	FUN();

	_entries = new FSEntry*[preallocate];

	if (_entries != nullptr)
		_entries_allocated = preallocate;
}

FSEntryList::~FSEntryList(){
	FUN();

	if (_managesEntries){
		for (size_t i = 0; i < _entries_used; i++){
			if (_entries[i] != nullptr)
				delete _entries[i];
		}
	}
}

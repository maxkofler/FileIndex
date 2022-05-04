#include "log.h"
#include "debug.h"

#include "namesDB.h"

#include <assert.h>
static_assert(sizeof(entry_namesDB*) + sizeof(void*) + sizeof(uint8_t) == sizeof(entry_namesDB), "Size of entry_namesDB changed, adjust this file!");

size_t NamesDB::add(std::string str, void* entry_insert){
	FUN();
	DEBUG_EX("NamesDB::add()");

	LOGMEM("Adding new name to database: \"" + str + "\"");

	//Not the amount of bytes needed for this entry
	uint8_t size_entry = sizeof(entry_namesDB) + str.length();

	//Allocate enough memory for this operation
	while(_size_entries * _blockSize < _used_bytes + size_entry)
		expand();

	//Get a pointer to the begin of this new entry
	entry_namesDB* entry = (entry_namesDB*)(_entries + _used_bytes);
	
	//Set this entry as the next entry for the previous entry
	if (_last_entry != nullptr)
		_last_entry->next = entry;

	//Set the entries carried entry
	entry->entry = entry_insert;

	//Set the entry name length and copy the name
	entry->nameLen = str.length();
	uint8_t* nameStart = _entries + _used_bytes + sizeof(entry_namesDB);
	std::memcpy(nameStart, str.c_str(), str.length());

	//Update the database
	_used_bytes += size_entry;
	_last_entry = entry;

	//Determine the id of this entry, add it and return it
	size_t id = _count_entries;
	_count_entries++;

	return id;
}

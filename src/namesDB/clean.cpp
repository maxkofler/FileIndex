#include "log.h"
#include "debug.h"

#include "namesDB.h"

void NamesDB::clean(){
	FUN();
	DEBUG_EX("NamesDB::clean()");

	if (_entries != nullptr){
		delete _entries;
		_entries = nullptr;
	}

	_size_entries = 0;
	_used_bytes = 0;
	_count_entries = 0;
	_last_entry = nullptr;
}

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
}

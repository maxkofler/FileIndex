#include "log.h"
#include "debug.h"

#include "namesDB.h"

void* NamesDB::getEntry(size_t id){
	FUN();
	DEBUG_EX("NamesDB::getEntry()");

	//Check if the ID is out of bounds
	if (id >= _count_entries){
		LOGE("ID " + std::to_string(id) + " is out of bounds");
		return nullptr;
	}


	//Get the pointer to the first entry
	entry_namesDB* curEntry = (entry_namesDB*)_entries;

	//Iterate over every entry until we found the entry
	for (size_t i = 1; i <= id; i++){
		if (curEntry->next != nullptr)
			curEntry = curEntry->next;
	}

	return curEntry->entry;
}

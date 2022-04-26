#include "log.h"
#include "debug.h"

#include "namesDB.h"

#include <assert.h>

static_assert(sizeof(entry_namesDB*) + sizeof(void*) + sizeof(uint8_t) == sizeof(entry_namesDB), "Size of entry_namesDB changed, adjust this file!");

std::string NamesDB::getName(size_t id){
	FUN();
	DEBUG_EX("NamesDB::getName()");

	//Check if the ID is out of bounds
	if (id >= _count_entries){
		LOGE("ID " + std::to_string(id) + " is out of bounds");
		return std::string();
	}

	//Get the pointer to the first entry
	entry_namesDB* curEntry = (entry_namesDB*)_entries;

	//Iterate over every entry until we found the entry
	for (size_t i = 1; i <= id; i++){
		if (curEntry->next != nullptr)
			curEntry = curEntry->next;
	}

	//Allocate memory for the name to copy to, including the nullterminator
	char* name_cStr = new char[curEntry->nameLen+1];

	//Construct a pointer to the start of the name in the _entries data block
	uint8_t* start_name = (uint8_t*) curEntry + sizeof(entry_namesDB);

	//Copy the name using memcpy and append the nullterminator
	std::memcpy(name_cStr, start_name, curEntry->nameLen);
	name_cStr[curEntry->nameLen] = 0;

	//Put the name into a std::string
	std::string ret = std::string(name_cStr);
	
	//Remove the memory for the buffered name
	delete[] name_cStr;

	return ret;
}

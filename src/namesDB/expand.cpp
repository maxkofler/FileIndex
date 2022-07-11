#include "log.h"
#include "debug.h"

#include "namesDB.h"

bool NamesDB::expand(uint8_t count){
	FUN();
	DEBUG_EX("NamesDB::expand()");

	LOGMEM("Expanding database by " + std::to_string(count) + " to " + std::to_string(_size_entries+count) + " blocks...");

	//If the entries field has not been allocated yet
	if (_entries == nullptr){
		//Allocate the memory needed
		_entries = new uint8_t[_blockSize * count];

		//Check if it is ok
		if (_entries == nullptr)
			return false;

		//Clear the memory out
		memset(_entries, 0, _blockSize*count);

		//We now have <count> blocks available
		_size_entries = count;
		return true;
	}

	//If the entries field already exists, expand it
	else {
		//Calculate the new memory needed
		size_t newCount = _size_entries + count;

		//Allocate the memory for the new field
		uint8_t* newEntries = new uint8_t[_blockSize * newCount];
		
		//Check if it is ok
		if (newEntries == nullptr)
			return false;

		//Clear the new memory
		memset(newEntries+(_size_entries*_blockSize), 0, _blockSize*count);

		//Copy the memory
		std::memcpy(newEntries, _entries, _size_entries*_blockSize);

		//Delete the old memory
		delete _entries;

		//Move the pointer
		_entries = newEntries;

		//We now have <newCount> blocks available
		_size_entries = newCount;
		return true;
	}

	return false;
}

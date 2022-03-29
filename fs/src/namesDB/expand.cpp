#include "log.h"
#include "namesDB.h"

void NamesDB::expand(){
	FUN();

	#ifdef DEBUG
	LOGMEM(	"Expanding DB memory from " + std::to_string(this->_bytes_reserved) +
			" by " + std::to_string(this->_block_size) + " bytes");
	#endif

	//Determine the new size
	size_t newSize = this->_bytes_reserved + this->_block_size;

	//Allocate the new memory
	fs_name_entry* newNames = (fs_name_entry*)malloc(newSize);

	//Copy the data
	std::memcpy(newNames, this->_names, this->_bytes_used);

	//Delete the old data
	free(this->_names);

	//Move the new data
	this->_names = newNames;

	//Note the new reserved size
	this->_bytes_reserved += this->_block_size;
}

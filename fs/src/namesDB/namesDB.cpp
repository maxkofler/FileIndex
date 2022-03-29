#include "log.h"
#include "namesDB.h"

NamesDB::NamesDB(size_t blockSize){
	FUN();

	this->_block_size = blockSize;

	this->_names = (fs_name_entry*) malloc(this->_block_size);
	this->_next_entry = this->_names;
	this->_bytes_reserved = this->_block_size;
}

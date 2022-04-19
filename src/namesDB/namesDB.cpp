#include "log.h"
#include "debug.h"

#include "namesDB.h"

NamesDB::NamesDB(size_t blockSize){
	FUN();
	DEBUG_EX("NamesDB::NamesDB()");

	LOGMEM("Creating new names database with block size " + std::to_string(blockSize));

	this->_blockSize = blockSize;

	this->expand(1);
}

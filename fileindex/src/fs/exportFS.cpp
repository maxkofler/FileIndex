#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests
void FS::exportFS(std::ostream& outStream){
	FUN();
	DEBUG_EX("FS::exportFS()");

	#warning TODO: Remove this function
	//outStream.write((char*)&_entries._size, sizeof(size_t));
	//outStream.write((char*)_entries._data, _entries._size*sizeof(fs_entry));
}

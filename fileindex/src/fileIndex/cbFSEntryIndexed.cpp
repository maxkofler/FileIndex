#include "log.h"
#include "debug.h"

#include "fileIndex.h"

void FileIndex::setCBFSEntryIndexed(void (*callback)(const std::string_view& path, size_t id, bool isDir)){
	FUN();
	DEBUG_EX("FileIndex::setCBFSEntryIndexed()");

	_callback_indexed = callback;
}

void FileIndex::removeCBFSEntryIndexed(){
	FUN();

	_callback_indexed = nullptr;
}

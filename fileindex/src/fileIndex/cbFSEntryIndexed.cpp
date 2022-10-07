#include "log.h"
#include "debug.h"

#include "fileIndex.h"

void FileIndex::setCBFSEntryIndexed(void (*callback)(const std::string_view& path, size_t id, bool isDir, void* udata), void* udata){
	FUN();
	DEBUG_EX("FileIndex::setCBFSEntryIndexed()");

	_callback_indexed = callback;
    _callback_udata = udata;
}

void FileIndex::removeCBFSEntryIndexed(){
	FUN();

    _callback_indexed = nullptr;
    _callback_udata = nullptr;
}

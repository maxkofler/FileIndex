#include "log.h"
#include "debug.h"

#include "fs.h"

#include <exception>

//TODO: Tests
bool FS::importFS(std::istream& instream){
	FUN();
	DEBUG_EX("FS::importFS()");

	_entries.clean();

	instream.read((char*)&_entries._size, sizeof(size_t));
	LOGMEM("[FS][importFS] Importing " + std::to_string(_entries._size) + " bytes into filesystem...");

	if (!instream){
		LOGE(	"[FS][importFS] Failed to import stream contents to filesystem: EOF in length header, read bytes: " + std::to_string(instream.gcount()));
		_entries.clean();
		return false;
	}

	_entries._allocated = _entries._size;
	_entries._data = new fs_entry[_entries._allocated];

	instream.read((char*)_entries._data, _entries._size*sizeof(fs_entry));
	if (!instream){
		LOGE(	"[FS][importFS] Failed to import stream contents to filesystem: EOF in data segment, read bytes: " + std::to_string(instream.gcount()));
		_entries.clean();
		return false;
	}

	return true;
}

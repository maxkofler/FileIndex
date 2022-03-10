#ifndef __FS_DIRECTORY_H__
#define __FS_DIRECTORY_H__

#include "fs_entry.h"

class Directory : public FSEntry{

public:
	Directory(std::string* name);

	FS::entry_type					type();

	void							addEntry(FSEntry* entry);

};

#endif
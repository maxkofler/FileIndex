#ifndef __FS_FILE_H__
#define __FS_FILE_H__

#include "fs_entry.h"

class File : public FSEntry{

public:
	File(std::string* name);

	FS::entry_type						type();

};

#endif
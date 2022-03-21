#ifndef __FS_FILE_H__
#define __FS_FILE_H__

class File;

#include "fs_entry.h"
#include "fs_name.h"

class File : public FSEntry{

public:
	/**
	 * @brief	Creates a new filesystem entry
	 * @param	name					A pointer to the name string
	 */
	File(fs_name name);

	entry_type							type();

};

#endif
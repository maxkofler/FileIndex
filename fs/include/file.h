#ifndef __FS_FILE_H__
#define __FS_FILE_H__

#include "fs_entry.h"

class File : public FSEntry{

public:
	/**
	 * @brief	Creates a new filesystem entry
	 * @param	name					A pointer to the name string
	 * @param	shouldManageMemory		If the memory should be managed by this class (default: false)
	 */
	File(std::string* name, bool ownsName = false);

	FS::entry_type						type();

};

#endif
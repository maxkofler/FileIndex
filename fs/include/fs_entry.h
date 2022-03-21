#ifndef __FILESYSTEM_ENTRY_H__
#define __FILESYSTEM_ENTRY_H__

class FSEntry;

enum entry_type{
	ENTRY_DIRECTORY,
	ENTRY_FILE,
	ENTRY_SYMLINK
};

#include <stdint.h>
#include <deque>
#include <string>

#include "fs_name.h"

class FSEntry{

public:
	/**
	 * @brief	Creates a new filesystem entry
	 * @param	name					A pointer to the fs_name
	 */
	FSEntry(fs_name name);
	virtual ~FSEntry();

	/**
	 * @brief	Returns the file system entry type
	 */
	virtual entry_type					type() = 0;

#ifndef FRIEND_FS_ENTRY
private:
#endif

	FSEntry*							_parent = nullptr;

	fs_name								_name;

};

#endif
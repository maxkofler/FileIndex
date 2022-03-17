#ifndef __FILESYSTEM_ENTRY_H__
#define __FILESYSTEM_ENTRY_H__

enum entry_type{
	ENTRY_DIRECTORY,
	ENTRY_FILE,
	ENTRY_SYMLINK
};

#include <stdint.h>
#include <deque>
#include <string>

class FSEntry{

public:
	/**
	 * @brief	Creates a new filesystem entry
	 * @param	name					A pointer to the name string
	 * @param	shouldManageMemory		If the memory should be managed by this class (default: false)
	 */
	FSEntry(std::string* name, bool shouldManageMemory);
	virtual ~FSEntry();

	/**
	 * @brief	Returns the file system entry type
	 */
	virtual entry_type					type() = 0;

#ifndef FRIEND_FS_ENTRY
private:
#endif

	FSEntry*							_parent = nullptr;

	bool								_ownsName = false;
	std::string*						_name = nullptr;

};

#endif
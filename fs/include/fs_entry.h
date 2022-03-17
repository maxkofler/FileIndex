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

	/**
	 * @brief	Returns the name of this filesystem entry
	 */
	std::string							getName();

	/**
	 * @brief	Returns a pointer to the filesystem entry name (can be nullptr!)
	 */
	std::string*						getNamePtr();

	/**
	 * @brief	Returns the parent of this filesystem entry, nullptr if this is the root
	 */
	FSEntry*							getParent();

	/**
	 * @brief	Uses the system fs api to get the relative path to the entry provided
	 * @param	entry					The target entry
	 */
	std::string							getPathTo(FSEntry* entry);

#ifndef FRIEND_FS_ENTRY
private:
#endif

	FSEntry*							_parent = nullptr;

	bool								_ownsName = false;
	std::string*						_name = nullptr;

};

#endif
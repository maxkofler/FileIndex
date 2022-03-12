#ifndef __FILESYSTEM_ENTRY_H__
#define __FILESYSTEM_ENTRY_H__

namespace FS{
	enum entry_type{
		ENTRY_DIRECTORY,
		ENTRY_FILE
	};
}

#include <stdint.h>
#include <vector>
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
	~FSEntry();

	/**
	 * @brief	Returns the file system entry type
	 */
	virtual FS::entry_type				type() = 0;

	/**
	 * @brief	Returns the path to this filesystem entry
	 */
	std::string							getPathString();

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
	 * @brief	Returns a vector containing all the parent directories
	 */
	std::vector<FSEntry*>				getParents();

#ifndef FRIEND_FS_ENTRY
private:
#endif

	FSEntry*							_parent = nullptr;

	bool								_ownsName = false;
	std::string*						_name = nullptr;

};

#endif
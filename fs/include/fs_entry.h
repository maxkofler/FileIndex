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
#include <string>

class FSEntry{

public:
	FSEntry(std::string* name);

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

	std::string*						_name = nullptr;

};

#endif
#ifndef __FS_DIRECTORY_H__
#define __FS_DIRECTORY_H__

#include "fs_entry.h"

#include <vector>

class Directory : public FSEntry{

public:
	/**
	 * @brief	Creates a new filesystem entry
	 * @param	name					A pointer to the name string
	 * @param	shouldManageMemory		If the memory should be managed by this class (default: false)
	 */
	Directory(std::string* name, bool ownsName = false);

	FS::entry_type						type();

	/**
	 * @brief	Adds the supplied filesystem entry to this directory
	 * @param	entry					The entry to add
	 */
	void								addEntry(FSEntry* entry);

	/**
	 * @brief	Returns a reference to the entries contained in this directory 
	 */
	std::vector<FSEntry*>&				getEntries();

private:
	std::vector<FSEntry*>				_entries;

};

#endif
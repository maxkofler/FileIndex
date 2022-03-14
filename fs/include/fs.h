#ifndef __FS_H__
#define __FS_H__

#include "fs_entry.h"
#include "directory.h"
#include "file.h"

#include <vector>

class FS{

public:
	FS(std::string rootName);
	~FS();

	/**
	 * @brief	Adds a new entry to the file systems
	 * @param	type			The type of the entry (DIR or FILE)
	 * @param	name			The name of the new entry
	 * @param	parent			The parent of the entry
	 * @return	FSEntry*		A pointer to the newly created entry
	 */
	FSEntry*					newEntry(entry_type type, std::string name, Directory* parent);

private:
	Directory*					_root;

	bool						_owns_names = true;
	std::vector<std::string>*	_names = nullptr;

	std::deque<FSEntry*>		_entries;

};

#endif
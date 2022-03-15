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
	 * @brief	Creates a new file system entry in this filesystem
	 * @param	type			The type of the entry (DIR or FILE)
	 * @param	name			The name of the new entry
	 * @param	parent			The parent of the entry, nullptr (default) = create in root directory
	 * @return	FSEntry*		A pointer to the newly created entry
	 */
	FSEntry*					createEntry(entry_type type, std::string name, Directory* parent = nullptr);

private:
	Directory*					_root;

	bool						_owns_names = true;
	std::vector<std::string>*	_names = nullptr;

	std::deque<FSEntry*>		_entries;

};

#endif
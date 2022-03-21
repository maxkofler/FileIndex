#ifndef __FS_H__
#define __FS_H__

#include "fs_entry.h"
#include "fs_name.h"
#include "directory.h"
#include "filesystem.h"
#include "file.h"

#include <vector>
#include <deque>

namespace FS{

	/**
	 * @brief	Returns the name of the supplied fs entry
	 * @param	entry				The entry to get the name of
	 */
	std::string						getName(FSEntry* entry);

	/**
	 * @brief	Returns the parent directory of the fs entry
	 * @param	entry				The entry to get the parent firectory of
	 */
	Directory*						getParent(FSEntry* entry);

	/**
	 * @brief	Returns the root directory of a fs entry
	 * @param	entry				The entry to process
	 */
	Directory*						getRoot(FSEntry* entry);

	/**
	 * @brief	Returns a deque containing all the fs entries constructing the path
	 * @param	entry				The entry to get the path of
	 */
	std::deque<FSEntry*>			getPath(FSEntry* entry);

	/**
	 * @brief	Returns the path to the provided fs entry
	 * @param	entry				The entry to get the path of
	 */
	std::string						getPathString(Filesystem* fs, FSEntry* entry);

	/**
	 * @brief	Returns the path to get from one entry to the other
	 * @param	from				The entry to start from
	 * @param	to					The entry to go to
	 */
	std::string						getPathTo(Filesystem* fs, FSEntry* from, FSEntry* to);
}

#endif
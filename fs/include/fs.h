#ifndef __FS_H__
#define __FS_H__

#include "fs_entry.h"
#include "directory.h"
#include "file.h"

#include <vector>
#include <deque>

namespace FS{
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
	std::string						getPathString(FSEntry* entry);
}

#endif
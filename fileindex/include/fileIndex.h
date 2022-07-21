#ifndef __FILEINDEX_H__
#define __FILEINDEX_H__

#include "namesDB.h"
#include "fstypes.h"

#include <string>

class FileIndex{

public:
	FileIndex(NamesDB* db = nullptr);
	~FileIndex();

	/**
	 * @brief	Indexes the supplied path if it is a directory
	 * @param	parent		The parent directory
	 * @param	path		The path to index
	 * @param	recursive	If this function should enter subdirectories (default: true)
	 * @return	uint64_t	The amount of entries found
	 */
	uint64_t				index(fs_dir* parent, std::string path, bool recursive = true);

	/**
	 * @brief	Returns a pointer to the internal database
	 */
	NamesDB*				getDB();

#ifndef FRIEND_FILEINDEX
private:
#endif

	NamesDB*				_db = nullptr;
	bool					_externalDB = false;

};

#endif

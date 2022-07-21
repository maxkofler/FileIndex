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

	/**
	 * @brief	Get the total amount of entries indexed by this class instance
	 */
	size_t					getIndexedEntriesCount();

	/**
	 * @brief	Get the total amount of duplicated names saved
	 */
	size_t					getSavedDuplicatesCount();

#ifndef FRIEND_FILEINDEX
private:
#endif

	/**
	 * @brief	The database used for storing the indexed entries
	 */
	NamesDB*				_db = nullptr;

	/**
	 * @brief	If the database was supplied externally
	 */
	bool					_externalDB = false;

	/**
	 * @brief	The amount of otherwise duplicated names saved
	 */
	size_t					_savedDuplicateNames = 0;

	/**
	 * @brief	The total amount of indexed entries
	 */
	size_t					_indexedEntries = 0;

	/**
	 * @brief	Appends the supplied entry to the database, if it already exists, it adds it to the crate
	 * @param	name		The name of the entry to add
	 * @param	entry		The new entry to add
	 */
	bool					db_add_entry(std::string name, fs_entry* entry);

};

#endif

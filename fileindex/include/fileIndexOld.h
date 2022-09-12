#ifndef __FILEINDEX_H__
#define __FILEINDEX_H__

#include "namesDB.h"
#include "fstypes.h"
#include "fsCrate.h"

#include <string>

class FileIndexOld{

public:
	FileIndexOld(NamesDB* db = nullptr);
	~FileIndexOld();

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

	/**
	 * @brief	Cleans up the dirty database and moves its optimized entries to the main db, clears the main db
	 * @return	size_t		The amount of entries transferred
	 */
	size_t					optimizeDB();

	void					cleanDirtyDB();

	void					cleanDB();

#ifndef FRIEND_FILEINDEX
private:
#endif

	/**
	 * @brief	The database used for storing the indexed entries
	 */
	NamesDB*				_db = nullptr;

	/**
	 * @brief	The uncleaned database used for indexing only, gets cleaned after indexing
	 */
	NamesDB*				_dirtyDB = nullptr;

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
	 * @brief	Indexes the supplied path blindly, no checks are made
	 * @param	parent		The parent directory
	 * @param	path		The path to index
	 * @param	recursive	If this function should enter subdirectories (default: true)
	 */
	void					index_blind(fs_dir* parent, std::string path, bool recursive = true);

	void					optimizeDuplicates(std::string& name, entry_namesDB* startEntry, size_t startEntryID);

	void					findAllExactMatchesFast(NamesDB* db, fs_crate* crate, std::string& nameString, entry_namesDB* entry, size_t id);

};

#endif

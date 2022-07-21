#ifndef __NAMES_DB_H__
#define __NAMES_DB_H__

#include <stdlib.h>			//size_t
#include <string>

//If the entry of a namesDB entry is submitted as nullptr, replace it with this
#define ENTRY_NULLPTR 0xFFFFFFFFFFFFFFFF

struct entry_namesDB{
	void*						entry;
	uint8_t						nameLen;
} __attribute__((packed));

#define SEARCHRES_NOTFOUND -1

struct namesDB_searchRes{
	int8_t						code = 0;
	void*						data;
	size_t						id;
	entry_namesDB*				dbEntry;
};

class NamesDB{

public:
	
	/**
	 * @brief	Creates a new names database
	 * @param	blockSize		The size of the blocks that get allocated
	 */
	NamesDB(size_t blockSize = 1024);
	~NamesDB();

	/**
	 * @brief	Expands the internal database by the supplied amount of blocks
	 * @param	count			The amount of blocks to expand by
	 * @return	If false, the database could not be expanded, DELETE IT AFTER A FAILURE!!!
	 * 			Typically this happens when the system is out of memory
	 */
	bool						expand(uint8_t count = 1);

	/**
	 * @brief	Cleans the whole database, including every allocated object
	 */
	void						clean();

	/**
	 * @brief	Adds the supplied string to the database
	 * @param	str				The string to add
	 * @param	entry			The entry to register
	 * @return	size_t			The id of the name
	 */
	size_t						add(std::string str, void* entry);

	/**
	 * @brief	Gets the entry with the specified id of this database (is really slow, read note)
	 * @param	id				The id to search (received from add())
	 * @return	void*			The entry previously supplied to add(), nullptr if out of range
	 * @note	This function is slow, it iterates over every entry, don't use it if not necessary
	 */
	void*						getEntry(size_t id);

	/**
	 * @brief	Gets the name string of the specified id (is really slow, read note)
	 * @param	id				The id to search (received from add())
	 * @return	std::string		The name previously supplied to add(), empty if out of range
	 * @note	This function is slow, it iterates over every entry, don't use it if not necessary
	 */
	std::string					getName(size_t id);

	/**
	 * @brief	Searches for the first occurrence of the specified name
	 * @param	name			The name to search for
	 * @param	start_id		The id to start searching from
	 * @return	namesDB_searchRes	The search result
	 */
	namesDB_searchRes			searchFirst(std::string name, size_t start_id = 0);

	/**
	 * @brief	Returns the amount of entries stored in this database
	 */
	size_t						getEntriesCount();

	/**
	 * @brief	Returns the bytes used by this database
	 */
	size_t						getBytesUsed();

#ifndef FRIEND_NAMES_DB
private:
#endif

	/**
	 * @brief	The size of the  allocations
	 */
	size_t						_blockSize;

	/**
	 * @brief	The size of the entries field in blocks
	 */
	size_t						_size_entries = 0;

	/**
	 * @brief	The bytes used of the entries block
	 */
	size_t						_used_bytes = 0;

	/**
	 * @brief	The amount of entries stored in this database
	 */
	size_t						_count_entries = 0;

	/**
	 * @brief	All the entries
	 * This is the entry point into the names, this is NOT an array!
	 * This is allocated in bytes, hence the uint8_t
	 */
	uint8_t*					_entries = nullptr;

	/**
	 * @brief	The last entry to fill in the next pointer
	 */
	entry_namesDB*				_last_entry = nullptr;

	/**
	 * @brief	Searches for the database entry with the supplied id and returns a pointer to it
	 * @param	id				The id of the searched entry
	 * @return	entry_namesDB*	A pointer to the db entry
	 */
	entry_namesDB*				getDBEntry(size_t id);

};

#endif
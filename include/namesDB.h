#ifndef __NAMES_DB_H__
#define __NAMES_DB_H__

#include <stdlib.h>			//size_t

struct entry_namesDB{
	struct entry_namesDB*		next;
	void*						entry;
	uint8_t						nameLen;
} __attribute__((packed));

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
	 * @return	size_t			The index of the string
	 */
	size_t						add(std::string str, void* entry);

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

};

#endif

#ifndef __NAMES_DB_H__
#define __NAMES_DB_H__

#include <stdlib.h>			//size_t

struct entry_namesDB{
	struct entry_namesDB*		prev;
	struct entry_namesDB*		next;
	void*						entry;
	uint8_t						nameLen;
	char*						name;
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
	 * @brief	All the entries
	 * This is the entry point into the names, this is NOT an array!
	 * This is allocated in bytes, hence the uint8_t
	 */
	uint8_t*					_entries = nullptr;

};

#endif

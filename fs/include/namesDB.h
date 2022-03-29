#ifndef __NAMES_DB_H__
#define __NAMES_DB_H__

#include "fs_name.h"

#include <string>

/**
 * @brief	This class implements a database for managing names
 * 			and having quick access to them, it allocates its memory using chunks
 * 			and aims to provide continous memory for its database
 */
class NamesDB{

public:
	/**
	 * @brief	Creates a new Database
	 * @param	blockSize			Size of blocks that get allocated in bytes (default = 4096)
	 */
	NamesDB(size_t blockSize = 4096);

	/**
	 * @brief	Adds the specified name to the database and checks for duplicates
	 * @param	name				The name to create
	 * @return	fs_name				The new name to use when getting the name from this DB
	 */
	fs_name							createName(std::string name);

	/**
	 * @brief	Expands the memory used by this database to the next multiple of _block_size
	 */
	void							expand();

private:
	/**
	 * @brief	The main array containing all the names
	 */
	fs_name_entry*					_names = nullptr;

	/**
	 * @brief	A pointer to the next entry location
	 */
	fs_name_entry*					_next_entry = nullptr;

	/**
	 * @brief	The database always allocates multiples of this size
	 */
	size_t							_block_size;

	/**
	 * @brief	The amount of bytes reserved
	 */
	size_t							_bytes_reserved = 0;

	/**
	 * @brief	The amount of bytes used
	 */
	size_t							_bytes_used = 0;

	
	//size_t							_names_used = 0;
	//size_t							_names_reserved = 0;
	//size_t							_names_requested = 0;

	/**
	 * @brief	The amount of bytes the current database uses
	 */
	//size_t							_bytes_used = 0;

	/**
	 * @brief	The amount of bytes the db has to work with
	 */
	//size_t							_bytes_reserved = 0;
};

#endif

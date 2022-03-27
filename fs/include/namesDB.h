#ifndef __NAMES_DB_H__
#define __NAMES_DB_H__

#include "fs_name.h"

/**
 * @brief	This class implements a database for managing names
 * 			and having quick access to them
 */
class NamesDB{

public:
	/**
	 * @brief	Creates a new Database
	 * @param	reserve				The amount of entries to reserver memory for (default: 100)
	 */
	NamesDB(size_t reserve = 100);



private:
	/**
	 * @brief	The main array containing all the names
	 * 
	 */
	fs_name_entry					_names[];

};

#endif

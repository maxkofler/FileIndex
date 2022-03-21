#ifndef __FS_NAME_H__
#define __FS_NAME_H__

#include <stdint.h>

#include "fs_entry_list.h"

/**
 * @brief	A fs_name_entry is an entry in the array of names
 */
typedef struct {

	FSEntryList*	entries;			//A pointer to the list containing the entries that point to this name
	uint8_t			len_name;			//The length of the name
	char*			name;				//The name pointer

} fs_name_entry;

/**
 * @brief A fs_name is a wrapper for the index into the array of names
 * 
 */
typedef struct {

	uint32_t	index;

} fs_name;

#endif
#ifndef __FS_NAME_H__
#define __FS_NAME_H__

#include <stdint.h>

#include "fs_entry_list.h"

#define TYPE_FS_NAME_ENTRY_ENTRIES 	FSEntryList*
#define TYPE_FS_NAME_ENTRY_LEN_NAME uint8_t
#define TYPE_FS_NAME_ENTRY_NAME		char

/**
 * @brief	A fs_name_entry is an entry in the array of names
 */
typedef struct {

	TYPE_FS_NAME_ENTRY_ENTRIES	entries;	//A pointer to the list containing the entries that point to this name
	TYPE_FS_NAME_ENTRY_LEN_NAME	len_name;	//The length of the name
	TYPE_FS_NAME_ENTRY_NAME		name[];		//The name pointer

} fs_name_entry;

/**
 * @brief A fs_name is a wrapper for the index into the array of names
 * 
 */
typedef struct {

	uint32_t	index;

} fs_name;

#endif
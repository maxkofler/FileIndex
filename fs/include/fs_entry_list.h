#ifndef __FS_ENTRY_LIST_H__
#define __FS_ENTRY_LIST_H__

class FSEntryList;

#include "fs_entry.h"

class FSEntryList{

public:
	/**
	 * @brief	Create a new list, preallocate some memory if needed
	 * @param	managesMemory	If this class should manage the memory of the entries
	 * @param	preallocate		The amount of preallocated space for entries
	 */
	FSEntryList(bool managesMemory = false, size_t preallocate = 0);
	~FSEntryList();

	/**
	 * @brief	Adds the provided entry to this list
	 * @param	entry				The entry to add
	 */
	void							addEntry(FSEntry* entry);

	/**
	 * @brief	Allocates new memory for this list
	 * @param	additionalAmount	The amount of entries to reserve memory for
	 */
	void							reallocate(size_t additionalAmount);

private:

	size_t							_entries_allocated = 0;
	size_t							_entries_used = 0;

	bool							_managesEntries;
	FSEntry**						_entries;

};

#endif
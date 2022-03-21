#ifndef __FS_DIRECTORY_H__
#define __FS_DIRECTORY_H__

class Directory;

#include "fs_entry.h"
#include "fs_name.h"

#include <deque>
#include <ostream>

class Directory : public FSEntry{

public:
	/**
	 * @brief	Creates a new filesystem entry
	 * @param	name					A pointer to the name string
	 */
	Directory(fs_name name);

	entry_type							type();

	/**
	 * @brief	Adds the supplied filesystem entry to this directory
	 * @param	entry					The entry to add
	 */
	void								addEntry(FSEntry* entry);

	/**
	 * @brief	Returns a reference to the entries contained in this directory
	 */
	std::deque<FSEntry*>&				getEntries();

	/**
	 * @brief	Returns a deque containing all the entries recursively
	 */
	std::deque<FSEntry*>				getRecursiveEntries();

	/**
	 * @brief	Outputs the entries recursively to the ostream
	 * @param	out						The ostream to output to
	 */
	void								printRecursiveEntries(std::ostream& out);

private:
	std::deque<FSEntry*>				_entries;

};

#endif
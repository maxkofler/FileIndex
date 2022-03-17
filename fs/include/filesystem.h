#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include "directory.h"

#include <vector>
#include <deque>

class Filesystem{

public:
	Filesystem(std::string rootName);
	~Filesystem();

	/**
	 * @brief	Creates a new file system entry in this filesystem
	 * @param	type				The type of the entry (DIR or FILE)
	 * @param	name				The name of the new entry
	 * @param	parent				The parent of the entry, nullptr (default) = create in root directory
	 * @return	FSEntry*			A pointer to the newly created entry
	 */
	FSEntry*						createEntry(entry_type type, std::string name, Directory* parent = nullptr);

	/**
	 * @brief	Allocates memory for the internal storage of the provided name
	 * @param	name				The name to store
	 */
	std::string*					createName(std::string name);

	/**
	 * @brief	Indexes the supplied directory to this filesystem
	 * @param	directory			The directory to index
	 * @param	recursive			If the indexing should be recursive (default: true)
	 */
	void							index(Directory* directory, bool recursive = true);

	/**
	 * @brief	Checks if the fs entry is of a certain type
	 * @param	type				The expected type
	 * @param	path				The path to check
	 * @param	isCritical			If true, an FS error when checking will throw an exception
	 */
	bool							is(entry_type type, std::string path, bool isCritical);

	/**
	 * @brief	Returns a pointer to this filesystems root directory
	 */
	Directory*						getRoot();

	size_t							getEntryCount(){return _entryCount;}
	size_t							getNamesRequested(){return _namesRequested;}
	size_t							getNamesAllocated(){return _namesAllocated;}
	size_t							getDuplicateNamesSaved(){return _duplicateNamesSaved;}

private:
	Directory*						_root;
	
	std::vector<std::string*>*		_cache_names = nullptr;
	std::deque<FSEntry*>*			_cache_entries = nullptr;

	size_t							_entryCount = 0;
	size_t							_namesRequested = 0;
	size_t							_namesAllocated = 0;
	size_t							_duplicateNamesSaved = 0;
	

};

#endif
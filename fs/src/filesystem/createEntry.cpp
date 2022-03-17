#include "log.h"
#include "fs.h"
#include "filesystem.h"
#include "fsError.h"
#include "fs_entry.h"

FSEntry* Filesystem::createEntry(entry_type type, std::string newName, Directory* parent){
	FUN();

	if (parent == nullptr)
		parent = _root;

	if (FS::getRoot(parent) != _root)
		throw new FSError("Tried to create new entry in directory not present in this filesystem");

	std::string* name = createName(newName);

	FSEntry* nE;

	switch (type){
		case ENTRY_DIRECTORY:
			nE = new Directory(name, false);
			break;
		
		case ENTRY_FILE:
			nE = new File(name, false);
			break;

		default:
			throw new FSError("Tried to create entry of unknown type");
	}

	_cache_entries->push_back(nE);
	parent->addEntry(nE);

	_entryCount++;

	return nE;
}

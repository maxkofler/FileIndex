#include "log.h"
#include "fs.h"
#include "fsError.h"
#include "fs_entry.h"

FSEntry* FS::createEntry(entry_type type, std::string newName, Directory* parent){
	FUN();

	if (parent == nullptr)
		parent = _root;

	if (FS::getRoot(parent) != _root)
		throw new FSError("Tried to create new entry in directory not present in this filesystem");

	//TODO: check for already exising filenames
	_names->push_back(new std::string(newName));
	std::string* name = _names->back();

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

	_entries.push_back(nE);
	parent->addEntry(nE);

	return nE;
}

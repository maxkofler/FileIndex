#include "log.h"
#include "fs.h"
#include "fsError.h"
#include "fs_entry.h"

FSEntry* FS::newEntry(entry_type type, std::string name, Directory* parent){
	FUN();

	if (parent == nullptr)
		parent = _root;

	if (parent->getRootEntry() != _root)
		throw new FSError("Tried to create new entry in directory not present in this filesystem");

	_names->push_back(name);

	FSEntry* nE;

	switch (type){
		case ENTRY_DIRECTORY:
			nE = new Directory(&(_names->back()), false);
			break;
		
		case ENTRY_FILE:
			nE = new File(&(_names->back()), false);
			break;

		default:
			throw new FSError("Tried to create entry of unknown type");
	}

	_entries.push_back(nE);
	_root->addEntry(nE);

	return nE;
}

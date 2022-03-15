#define FRIEND_FS_ENTRY
#include "log.h"
#include "fs.h"
#include "fs_entry.h"
#include "fsError.h"

Directory* FS::getRoot(FSEntry* entry){
	FUN();

	FSEntry* last = entry;

	while(last->_parent != nullptr){
		last = last->_parent;
	}

	if (last->type() == ENTRY_DIRECTORY)
		return (Directory*)last;
	else
		throw new FSError("Root is not a directory");
}

#define FRIEND_NAMES_DB

#include "log.h"
#include "fileIndex.h"

#include <string>

size_t FileIndex::optimizeDB(){
	FUN();

	_db->clean();

	#warning This function (FileIndex::optimizeDB()) is not complete!

	entry_namesDB* curEntry = (entry_namesDB*)_dirtyDB->_entries;
	std::string curName;

	for (size_t i = 0; i < _dirtyDB->getEntriesCount(); i++, curEntry = NamesDB::getNextEntry(curEntry)){

		//Ignore entries with values as nullptr, those have already been cleaned
		if (curEntry->entry == nullptr)
			continue;

		curName = NamesDB::getEntryName(curEntry);

		optimizeDuplicates(curName, curEntry, i);

	}

	return 0;
}

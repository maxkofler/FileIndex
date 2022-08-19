//Make this file a friend of NamesDB so the custom searchAll() function can work
#define FRIEND_NAMES_DB

#include "log.h"
#include "fileIndex.h"
#include "fsCrate.h"

#include <deque>

void FileIndex::optimizeDuplicates(std::string& name, entry_namesDB* startEntry, size_t startEntryID){
	FUN();

	//entry_namesDB* cleanDBEntry = db_add_entry(name, (fs_entry*)startEntry->data);
	//fs_crate* cleanDBCrate = (fs_crate*)cleanDBEntry->data;

	fs_crate* cleanDBCrate = new fs_crate;
	_db->add(name, cleanDBCrate);

	findAllExactMatchesFast(_dirtyDB, cleanDBCrate, name, NamesDB::getNextEntry(startEntry), startEntryID+1);

	if (cleanDBCrate->count > 1)
		LOGD("[FileIndex][optimizeDuplicates] Total count of \"" + name + "\": " + std::to_string(cleanDBCrate->count));
}

void FileIndex::findAllExactMatchesFast(NamesDB* db, fs_crate* crate, std::string& nameString, entry_namesDB* entry, size_t id){

	bool proceed = true;
	
	size_t nameLen = nameString.length();
	const char* nameCStr = nameString.c_str();
	char* name_entry;

	size_t posStr = 0;
	size_t db_size = db->_count_entries;
	bool ok = true;

	for (; id < db_size; id++, entry = (entry_namesDB*)(((uint8_t*)entry) + sizeof(entry_namesDB) + entry->nameLen)){

		if (entry->data == nullptr)
			continue;

		if (entry->nameLen != nameLen)
			continue;

		ok = true;
		name_entry = (char*)entry + sizeof(entry_namesDB);

		for (posStr = 0; ok && posStr < entry->nameLen; posStr++){
			if (name_entry[posStr] != nameCStr[posStr])
				ok = false;
		}

		if (ok){
			FSCrate_add(crate, (fs_entry*)entry->data);
			entry->data = nullptr;
			_savedDuplicateNames++;
		}
	}
}

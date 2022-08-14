//Make this file a friend of NamesDB so the custom searchAll() function can work
#define FRIEND_NAMES_DB

#include "log.h"
#include "fileIndex.h"
#include "fsCrate.h"

#include <deque>

void findAllExactMatchesFast(NamesDB* db, fs_crate* crate, std::string nameString, entry_namesDB* entry, size_t id);

void FileIndex::optimizeDuplicates(std::string name, entry_namesDB* startEntry, size_t startEntryID){
	FUN();

	entry_namesDB* cleanDBEntry = db_add_entry(name, (fs_entry*)startEntry->data);
	fs_crate* cleanDBCrate = (fs_crate*)cleanDBEntry->data;

	findAllExactMatchesFast(_dirtyDB, cleanDBCrate, name, NamesDB::getNextEntry(startEntry), startEntryID+1);

	/*
	while(true){
		curRes.id += 1;
		curRes = _dirtyDB->searchFirstFromEntry(name, NamesDB::getNextEntry(curRes.dbEntry), curRes.id, true);

		if (curRes.code != 0){
			break;
		}

		if (curRes.data != nullptr){
			FSCrate_add(cleanDBCrate, (fs_entry*)curRes.data);
			curRes.dbEntry->data = nullptr;
			_savedDuplicateNames++;
		}
	}
	*/

	if (cleanDBCrate->count > 1)
		LOGD("[FileIndex][optimizeDuplicates] Total count of \"" + name + "\": " + std::to_string(cleanDBCrate->count));
}

void findAllExactMatchesFast(NamesDB* db, fs_crate* crate, std::string nameString, entry_namesDB* entry, size_t id){

	bool proceed = true;
	
	size_t nameLen = nameString.length();
	const char* nameCStr = nameString.c_str();
	char* name_entry;

	size_t posStr = 0;

	while(proceed){

		if (entry->nameLen == nameLen && entry->data != nullptr){
			name_entry = (char*)entry + sizeof(entry_namesDB);

			//Begin checking every character
			bool ok = true;
			for (posStr = 0; ok == true && posStr < entry->nameLen; posStr++){
				if (name_entry[posStr] != nameCStr[posStr])
					ok = false;
			}

			if (ok){
				FSCrate_add(crate, (fs_entry*)entry->data);
				entry->data = nullptr;
			}
		}

		entry = NamesDB::getNextEntry(entry);
		id++;

		if (id >= db->_count_entries)
			proceed = false;
	}
}

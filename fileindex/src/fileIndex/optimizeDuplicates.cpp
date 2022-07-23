#include "log.h"
#include "fileIndex.h"
#include "fsCrate.h"

void FileIndex::optimizeDuplicates(std::string name, entry_namesDB* startEntry, size_t startEntryID){
	FUN();

	entry_namesDB* cleanDBEntry = db_add_entry(name, (fs_entry*)startEntry->data);
	fs_crate* cleanDBCrate = (fs_crate*)cleanDBEntry->data;

	namesDB_searchRes curRes;
	curRes.dbEntry = startEntry;
	curRes.id = startEntryID-1;

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

	if (cleanDBCrate->count > 1)
		LOGD("[FileIndex][optimizeDuplicates] Total count of \"" + name + "\": " + std::to_string(cleanDBCrate->count));
}

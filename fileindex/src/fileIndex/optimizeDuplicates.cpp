#include "log.h"
#include "fileIndex.h"
#include "fsCrate.h"

void FileIndex::optimizeDuplicates(std::string name, entry_namesDB* startEntry, size_t startEntryID){
	FUN();

	entry_namesDB* cleanDBEntry = db_add_entry(name, (fs_entry*)startEntry->entry);
	fs_crate* cleanDBCrate = (fs_crate*)cleanDBEntry->entry;

	namesDB_searchRes curRes = _dirtyDB->searchFirst(name, startEntryID);

	while (curRes.code == 0){

		if (curRes.data != nullptr){
			LOGD("[FileIndex][optimizeDuplicates] Found duplicate for \"" + name + "\" at id=" + std::to_string(curRes.id));
			FSCrate_add(cleanDBCrate, (fs_entry*)curRes.data);
			curRes.dbEntry->entry = nullptr;
		}

		curRes = _dirtyDB->searchFirst(name, curRes.id+1);
	}

	if (cleanDBCrate->count > 1)
		LOGD("[FileIndex][optimizeDuplicates] Total count of \"" + name + "\": " + std::to_string(cleanDBCrate->count));
}

#include "log.h"
#include "fileIndex.h"
#include "fsCrate.h"

entry_namesDB* FileIndex::db_add_entry(std::string name, fs_entry* entry){
	FUN();

	namesDB_searchRes searchRes = _db->searchFirst(name, true);
	fs_crate* crate = nullptr;

	if (searchRes.code == 0){
		//If there exists already a name
		LOGMEM("[FileIndex][db_add_entry] Adding entry for name \"" + name + "\" to existing crate");
		crate = (fs_crate*) searchRes.data;
		_savedDuplicateNames++;
	} else if (searchRes.code == SEARCHRES_NOTFOUND || _db->getEntriesCount() == 0){
		//If there is no existing name
		LOGMEM("[FileIndex][db_add_entry] Creating new crate for name \"" + name + "\"");
		crate = new fs_crate;
		size_t db_id = _db->add(name, crate);
		searchRes.dbEntry = _db->getDBEntry(db_id);
	} else {
		LOGE("[FileIndex][db_add_entry] Database error when checking for existing names");
		return nullptr;
	}

	FSCrate_add(crate, entry);
	_indexedEntries++;

	return searchRes.dbEntry;
}

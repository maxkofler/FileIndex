#include "log.h"
#include "namesDB.h"

fs_name NamesDB::createName(std::string name){
	FUN();

	fs_name ret;

	#ifdef DEBUG
	LOGD("Creating new name \"" + name + "\"");
	#endif

	size_t size_newEntry = sizeof(TYPE_FS_NAME_ENTRY_ENTRIES) + sizeof(TYPE_FS_NAME_ENTRY_LEN_NAME);
	size_newEntry += (name.length() + 1) * sizeof(TYPE_FS_NAME_ENTRY_NAME);

	{//Check for enough space
		while (this->_bytes_used + size_newEntry >= this->_bytes_reserved){
			this->expand();
		}
	}

	{	//Copy the data to the new entry
		fs_name_entry* newEntry = this->_next_entry;
		newEntry->entries = new FSEntryList();
		newEntry->len_name = name.length();
		std::strcpy(newEntry->name, name.c_str());
	}

	{	//Move the next entry ahead
		this->_next_entry = (fs_name_entry*)(((uint8_t*)this->_next_entry) + size_newEntry);
		this->_bytes_used += size_newEntry;
	}

	return ret;
}

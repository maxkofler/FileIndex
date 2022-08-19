#include "log.h"
#include "fsCrate.h"

uint32_t FSCrate_expand(fs_crate* crate, uint32_t amount){
	FUN();

	//This does not touch the crate->count variable because that indicates how many entries are stored
	//in the array and NOT how many places are available

	if (crate == nullptr){
		LOGE("[FSCrate][expand] Tried to expand nullptr crate");
		return 0;
	}

	uint32_t prevCount = crate->count;
	uint32_t newSpace = prevCount + amount;

	LOGMEM("[FSCrate][expand] Expanding crate to " + std::to_string(newSpace) + " entries...");

	//Allocate memory for the new array
	fs_entry** newEntries = new fs_entry*[newSpace];

	//Copy the old array if there was an old array
	if (crate->entries != nullptr){
		for (uint32_t i = 0; i < prevCount; i++){
			newEntries[i] = crate->entries[i];
		}
	}

	//Delete the old array if one exists
	if (crate->entries != nullptr)
		delete crate->entries;

	//Set the new entries
	crate->entries = newEntries;

	return newSpace;
}

uint32_t FSCrate_add(fs_crate* crate, fs_entry* entry){
	FUN();

	if (crate == nullptr){
		LOGE("[FSCrate][add] Tried to add to nullptr crate");
		return 0;
	}

	if (entry == nullptr)
		LOGW("[W][FSCrate][add] Adding nullptr entry to crate");

	//Expand the crate by 1
	uint32_t expandRes = FSCrate_expand(crate);

	if (expandRes == 0)
		return expandRes;

	crate->entries[crate->count] = entry;
	crate->count++;

	return crate->count;
}

uint32_t FSCrate_add(fs_crate* crate, fs_entry** entries, uint32_t amount){
	FUN();

	if (crate == nullptr){
		LOGE("[FSCrate][add] Tried to add to nullptr crate");
		return 0;
	}

	if (entries == nullptr){
		LOGE("[FSCrate][add] Tried to add nullptr entry array to crate");
		return 0;
	}

	//Expand the crate by the needed amount
	uint32_t expandRes = FSCrate_expand(crate, amount);

	if (expandRes == 0)
		return expandRes;

	for (size_t i = 0; i < amount; i++){
		crate->entries[crate->count] = entries[i];
		crate->count++;
	}

	return crate->count;
}

#include "log.h"

#include "fstypes.h"

FSEntry::FSEntry(std::string isDir_, std::string id_, std::string name_, std::string nameID_, std::string parentID_)
: isDir(std::stoi(isDir_)), id(std::stoi(id_)), name(name_), nameID(std::stoi(nameID_)), parentID(std::stoi(parentID_)){
	FUN();

	LOGMEM("[FSEntry] Parsing new FSEntry");
}

FSEntry::FSEntry(bool isDir_, uint64_t id_, const std::string& name_, uint64_t nameID_, uint64_t parentID_)
: isDir(isDir_), id(id_), name(name_), nameID(nameID_), parentID(parentID_){
	FUN();

	LOGMEM("[FSEntry] Creating new FSEntry");
}

FSDir::FSDir(std::string id, std::string name, std::string nameID, std::string parentID)
: FSEntry("1", id, name, nameID, parentID){
	FUN();

	LOGMEM("[FSDir] Creating new FSDir");
}

FSDir::FSDir(const FSEntry& other)
: FSEntry(true, other.id, other.name, other.nameID, other.parentID){
	FUN();

	LOGMEM("[FSDir] Creating new FSDir from FSEntry");
}

FSDir::FSDir(const FSEntry* other)
: FSEntry(true, other->id, other->name, other->nameID, other->parentID){
	FUN();

	LOGMEM("[FSDir] Creating new FSDir from FSEntry pointer");
}

FSDir::~FSDir(){
	FUN();

	for (FSEntry* i : this->members){
		LOGMEM("[FSDir][" + this->name + "] Deleting member " + i->name);
		delete i;
	}
}

std::string FSDir::getRecMembersString(size_t depth){
	std::string ret;

	for (FSEntry* entry : this->members){
		for (size_t i = 0; i < depth; i++)
			ret += "_";
		ret += entry->name + "\n";

		if (entry->isDir)
			ret += ((FSDir*)entry)->getRecMembersString(depth+1);
	}

	return ret;
}

#include "log.h"

#include "fstypes.h"

FSEntry::FSEntry(FSDir* parent_, std::string isDir_, std::string id_, std::string name_, std::string nameID_, std::string parentID_)
: parent(parent_), isDir(std::stoi(isDir_)), id(std::stoi(id_)), name(name_), nameID(std::stoi(nameID_)), parentID(std::stoi(parentID_)){
	FUN();

	LOGMEM("[FSEntry] Parsing new FSEntry");
}

FSEntry::FSEntry(FSDir* parent_, bool isDir_, uint64_t id_, const std::string& name_, uint64_t nameID_, uint64_t parentID_)
: parent(parent_), isDir(isDir_), id(id_), name(name_), nameID(nameID_), parentID(parentID_){
	FUN();

	LOGMEM("[FSEntry] Creating new FSEntry");
}

std::shared_ptr<FSEntry> FSEntry::child(size_t pos){
	FUN();

	if (!this->isDir)
		return nullptr;

	FSDir* th = (FSDir*)this;

	if (pos >= th->children.size())
		return nullptr;

	return th->children.at(pos);
}

size_t FSEntry::childCount(){
	FUN();

	if (!this->isDir)
		return 0;

	return ((FSDir*)this)->children.size();
}

size_t FSEntry::childNumber(){
	FUN();

    if (parent != nullptr)
		for (size_t i = 0; i < parent->children.size(); i++)
			if (parent->children.at(i).get() == this)
				return i;

	return 0;
}

//
// FSDIR
//

FSDir::FSDir(FSDir* parent, std::string id, std::string name, std::string nameID, std::string parentID)
: FSEntry(parent, "1", id, name, nameID, parentID){
	FUN();

	LOGMEM("[FSDir] Creating new FSDir");
}

FSDir::FSDir(const FSEntry& other)
: FSEntry(other.parent, true, other.id, other.name, other.nameID, other.parentID){
	FUN();

	LOGMEM("[FSDir] Creating new FSDir from FSEntry");
}

FSDir::FSDir(const FSEntry* other)
: FSEntry(other->parent, true, other->id, other->name, other->nameID, other->parentID){
	FUN();

	LOGMEM("[FSDir] Creating new FSDir from FSEntry pointer");
}

std::string FSDir::getRecChildrenString(size_t depth){
	std::string ret;

	for (auto entry : this->children){
		for (size_t i = 0; i < depth; i++)
			ret += "_";
		ret += entry->name;
		if (entry->parent){
			ret += "(parent=" + entry->parent->name;
			ret += " childNumber=" + std::to_string(entry->childNumber());
			ret += " childCount=" + std::to_string(entry->childCount());
			ret += ")";
		}
		ret += "\n";

		if (entry->isDir)
			ret += ((FSDir*)entry.get())->getRecChildrenString(depth+1);
	}

	return ret;
}

void FSDir::sortChildrenRec(){
	FUN();

	std::sort(this->children.begin(), this->children.end(), [](const std::shared_ptr<FSEntry>& first, const std::shared_ptr<FSEntry>& second){

		if (first->isDir)
			((FSDir*)first.get())->sortChildrenRec();

		return std::lexicographical_compare(
			first->name.begin(), first->name.end(),
			second->name.begin(), second->name.end(),
			[](const char& char1, const char& char2) {
				return tolower(char1) < tolower(char2);
			}
		);
	});
}

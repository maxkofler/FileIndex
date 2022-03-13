#include "log.h"
#include "fs_entry.h"

#include <filesystem>
namespace fs = std::filesystem;

std::string FSEntry::getPathTo(FSEntry* entry){
	FUN();

	fs::path this_entry = getPathString();
	fs::path other_entry = entry->getPathString();

	return fs::relative(other_entry, this_entry);
}

#include "log.h"
#include "directory.h"
#include "fsError.h"

void Directory::printRecursiveEntries(std::ostream& out){
	FUN();

	if (!out.good())
		throw new FSError("Output stream is bad");

	auto entries = getRecursiveEntries();

	if (entries.size() > 0){
		FSEntry* last = this;
		for (FSEntry* entry : entries){
			out << last->getPathTo(entry);
			if (entry->type() == ENTRY_DIRECTORY){
				out << '/';
				last = entry;
			}
			out << std::endl;
		}
	}
}

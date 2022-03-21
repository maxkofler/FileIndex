#include "log.h"
#include "filesystem.h"
#include "fsError.h"

void Filesystem::printIndex(std::ostream& stream){
	FUN();

	if (stream.bad())
		throw new FSError("Output stream is bad");

	//First output all the names
	for (std::string* name : *_cache_names){
		stream << *name << std::endl;
	}

	//TODO: output the index
}

#include "log.h"
#include "filesystem.h"

std::string* Filesystem::createName(std::string nameContent){
	FUN();

	_namesRequested++;

	for (std::string* name : *_names){
		if (*name == nameContent){
			_duplicateNamesSaved++;
			return name;
		}
	}

	_namesAllocated++;

	std::string* res = new std::string(nameContent);
	res->shrink_to_fit();
	_names->push_back(res);
	return res;
}

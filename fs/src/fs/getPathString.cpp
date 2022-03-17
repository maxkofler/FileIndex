#define FRIEND_FS_ENTRY
#include "log.h"
#include "fs.h"

std::string FS::getPathString(FSEntry* entry){
	FUN();

	auto path = getPath(entry);
	std::string res = "";

	for (FSEntry* entry : path){
		res += FS::getName(entry) + '/';
	}

	if (path.back()->type() != ENTRY_DIRECTORY)
		res.erase(res.size()-1, 1);

	return res;
}

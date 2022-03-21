#define FRIEND_FS_ENTRY
#include "log.h"
#include "fs.h"

std::string FS::getPathString(Filesystem* fs, FSEntry* entry){
	FUN();

	auto path = getPath(entry);
	std::string res = "";

	for (FSEntry* entry : path){
		res += fs->getName(entry) + '/';
	}

	if (path.back()->type() != ENTRY_DIRECTORY)
		res.erase(res.size()-1, 1);

	return res;
}

#include "log.h"
#include "fs.h"
#include "fsError.h"

std::string FS::getPathTo(Filesystem* fs, FSEntry* from, FSEntry* to){
	FUN();

	if (from == nullptr)
		throw new FSError("Tried to get path from nullptr");

	if (to == nullptr)
		throw new FSError("Tried to get path to nullptr");

	//Check if the entries share the same root
	if (FS::getRoot(from) != FS::getRoot(to))
		throw new FSError("Tried to get path to entries under different roots");

	//Get the paths to the files
	auto path_this = FS::getPath(from);
	auto path_other = FS::getPath(to);

	//Until there are no differences in the path, don't care
	int pos = 0;
	for(pos = 0; (pos < path_other.size() || pos+1 >= path_this.size()); pos++){
		if (path_other[pos] != path_this[pos])
			break;
	}

	std::string path;

	//On difference, get the levels from the difference to this item for inserting "../"
	int levelsToThis = path_this.size() - pos;
	for (int i = 0; i < levelsToThis; i++){
		path += "../";
	}

	//Then add the path from the entry of difference to the desired entry
	for (int i = pos; i < path_other.size(); i++){
		path += fs->getName(path_other[i]) + '/';
	}

	//Cut the last '/'
	if (path[path.length() - 1 ] == '/')
		path.erase(path.length()-1);

	#ifdef DEBUG
	LOGF("Calculated path from " + FS::getPathString(from) + " to " + FS::getPathString(to) + ": " + path);
	#endif

	return path;
}

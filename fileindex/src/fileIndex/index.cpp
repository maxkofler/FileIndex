#include "log.h"
#include "fileIndex.h"

#include <filesystem>

uint64_t FileIndex::index(std::string pathStr, bool recursive){
	FUN();

	namespace fs = std::filesystem;
	std::error_code ec;

	//Check if the path even exists
	bool exists = fs::exists(pathStr, ec);
	if (ec){
		LOGUE("[FileIndex][index] Failed to check path \"" + pathStr + "\": " + ec.message());
		return 0;
	}

	if (!exists){
		LOGUE("[FileIndex][index] Path to index \"" + pathStr + "\" does not exist");
		return 0;
	}

	//Check if the path is a directory
	bool isDir = fs::is_directory(pathStr, ec);
	if (ec){
		LOGUE("[FileIndex][index] Failed to check path \"" + pathStr + "\": " + ec.message());
		return 0;
	}

	if (!isDir){
		LOGUE("[FileIndex][index] Path to index \"" + pathStr + "\" is not a directory");
		return 0;
	}

	fs_dir rootDir;
	rootDir.parentID = 0;

	size_t rootID = add(pathStr, rootDir);

	index_blind(rootID, pathStr, recursive);

	return _indexedEntries;
}

#include "log.h"
#include "fileIndex.h"

#include <filesystem>

uint64_t FileIndex::index(fs_dir* parent, std::string pathStr, bool recursive){
	FUN();

	namespace fs = std::filesystem;
	std::error_code ec;

	if (parent == nullptr){
		LOGUE("[FileIndex][index] Tried to add new entries to nullptr directory");
		return 0;
	}

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

	//Create the iterator
	fs::directory_iterator dirIt(pathStr, ec);
	if (ec){
		LOGUE("[FileIndex][index] Failed to create directory iterator for \"" + pathStr + "\": " + ec.message());
		return 0;
	}

	std::string curPath, curName;
	uint64_t indexedFiles = 0;

	//Start indexing
	for (fs::directory_entry entry : dirIt){
		curPath = entry.path().string();
		curName = entry.path().stem().string() + entry.path().extension().string();
		LOGF("[FileIndex][index] Found directory entry \"" + curPath + "\", DB name: \"" + curName + "\"");

		//Ignore symlinks
		if (entry.is_symlink())
			continue;
		
		//Add directories and enter them if wanted
		if (entry.is_directory()){

			fs_dir* newDir = new fs_dir;
			newDir->parent = parent;

			db_add_entry(curName, newDir);

			if (recursive){
				LOGIO("[FileIndex][index] Entering directory \"" + curPath + "\"");
				index(newDir, curPath, recursive);
			}
		} else {

			fs_file* newFile = new fs_file;
			newFile->parent = parent;
			
			db_add_entry(curName, newFile);
		}

		indexedFiles++;
	}

	LOGMEM("[FileIndex][index] Indexed " + std::to_string(indexedFiles) + " files");

	return indexedFiles;
}

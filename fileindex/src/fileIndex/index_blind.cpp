#include "log.h"
#include "fileIndex.h"

#include <filesystem>

namespace fs = std::filesystem;

void FileIndex::index_blind(size_t parentID, std::string pathStr, bool recursive){
	FUN();

	std::error_code ec;

	//Create the directory iterator
	fs::directory_iterator dirIt(pathStr, ec);
	if (ec){
		LOGUE("[FileIndex][index] Failed to create directory iterator for \"" + pathStr + "\": " + ec.message());
		return;
	}

	std::string curPath, curName;
	bool isDir = false;

	//Start indexing
	for (fs::directory_entry entry : dirIt){
		curPath = entry.path().string();
		curName = entry.path().stem().string() + entry.path().extension().string();
		LOGF("[FileIndex][index] Found directory entry \"" + curPath + "\", DB name: \"" + curName + "\"");

		//Ignore symlinks
		if (entry.is_symlink())
			continue;

		isDir = entry.is_directory();

		//Add directories and enter them if wanted
		if (isDir){

			fs_dir newDir;
			newDir.parentID = parentID;

			size_t dirID = add(curName, newDir);

			if (recursive){
				LOGIO("[FileIndex][index] Entering directory \"" + curPath + "\"");
				index_blind(dirID, curPath, recursive);
			}
		} else {

			fs_file newFile;
			newFile.parentID = parentID;
			
			_fs->add(curName, newFile);
		}

		if (_callback_indexed != nullptr)
			_callback_indexed(curPath, _indexedEntries, isDir);

		_indexedEntries++;
	}

	LOGMEM("[FileIndex][index] Indexed " + std::to_string(_indexedEntries) + " files");
}

#include "log.h"
#include "fileIndex.h"

#include <filesystem>

namespace fs = std::filesystem;

void FileIndex::index_blind(fs_dir* parent, std::string pathStr, bool recursive){
	FUN();

	std::error_code ec;

	//Create the directory iterator
	fs::directory_iterator dirIt(pathStr, ec);
	if (ec){
		LOGUE("[FileIndex][index] Failed to create directory iterator for \"" + pathStr + "\": " + ec.message());
		return;
	}

	std::string curPath, curName;

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

			_dirtyDB->add(curName, (fs_entry*)newDir);
			//_db->add(curName, (fs_entry*)newDir);

			if (recursive){
				LOGIO("[FileIndex][index] Entering directory \"" + curPath + "\"");
				index_blind(newDir, curPath, recursive);
			}
		} else {

			fs_file* newFile = new fs_file;
			newFile->parent = parent;
			
			_dirtyDB->add(curName, (fs_entry*)newFile);
			//_db->add(curName, (fs_entry*)newFile);
		}

		_indexedEntries++;
	}

	LOGMEM("[FileIndex][index] Indexed " + std::to_string(_indexedEntries) + " files");
}
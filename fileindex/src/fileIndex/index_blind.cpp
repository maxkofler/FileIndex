#include "log.h"
#include "fileIndex.h"

#include <filesystem>

#ifdef _WIN32
	#include <Windows.h>
	std::string ConvertWideToUtf8(const std::wstring& wstr){
		int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL);
		std::string str(count, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
		return str;
	}
#endif

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
		#ifdef _WIN32
			curPath = ConvertWideToUtf8(entry.path().wstring());
			curName = ConvertWideToUtf8(entry.path().stem().wstring()) + ConvertWideToUtf8(entry.path().extension().wstring());
		#else
			curPath = entry.path().string();
			curName = entry.path().stem().string() + entry.path().extension().string();
		#endif
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
            _callback_indexed(curPath, _indexedEntries, isDir, _callback_udata);

		_indexedEntries++;
	}

	LOGMEM("[FileIndex][index] Indexed " + std::to_string(_indexedEntries) + " files");
}

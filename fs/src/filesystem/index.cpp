#define FRIEND_FS_ENTRY
#include "log.h"
#include "fs.h"
#include "filesystem.h"
#include "fsError.h"
#include "fs_entry.h"

#include <filesystem>
namespace fs = std::filesystem;

void Filesystem::index(Directory* directory, bool recursive){
	FUN();

	if (directory == nullptr)
		directory = _root;

	std::string dirPath = FS::getPathString(this, directory);

	if (!is(ENTRY_DIRECTORY, dirPath, false))
		throw new FSError("Tried to index non-directory");

	std::error_code ec;
	fs::directory_iterator iterator(dirPath, ec);

	if (ec)
		LOGW("Failed to create directory iterator for " + dirPath + ": " + ec.message());

	#ifdef DEBUG
	LOGF("Indexing directory " + dirPath);
	#endif

	for (fs::directory_entry entry : iterator){
		std::string entryPath = entry.path().string();
		std::string entryName = entry.path().filename().string();

		if (is(ENTRY_SYMLINK, entryPath, false))
			continue;

		bool isDir = is(ENTRY_DIRECTORY, entryPath, false);

		//Create the new entry
		FSEntry* newEntry;

		if (isDir)
			newEntry = createEntry(ENTRY_DIRECTORY, entryName, directory);
		else
			newEntry = createEntry(ENTRY_FILE, entryName, directory);

		if (recursive && isDir)
			index((Directory*)newEntry, recursive);
	}
}

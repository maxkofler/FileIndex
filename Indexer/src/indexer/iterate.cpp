#include "log.h"
#include "indexer.h"
#include "indexerError.h"

#include "directory.h"
#include "file.h"

#include <filesystem>

namespace fs = std::filesystem;

void Indexer::iterate(Directory* directory){
	FUN();

	std::string name = directory->getName();
	std::string path = directory->getPathString();

	std::error_code ec;
	fs::directory_iterator it(path, ec);

	if (ec){
		if (_failOnError)
			throw new IndexerError("FS error while trying to iterate " + path + ": " + ec.message());
		else {
			LOGW("WARNING: FS error while trying to iterate " + path + ": " + ec.message() + ", trying to continue");
			return;
		}
	}

	for (fs::directory_entry entry : it){
		if (isSymlink(entry.path().string(), false)){
			#ifdef DEBUG
			LOGI("Skipping symlink " + entry.path().string());
			#endif
			continue;
		}

		bool isDir = isDirectory(entry.path().string(), false);

		FSEntry* newEntry;
		
		if (isDir)
			newEntry = new Directory(new std::string(entry.path().filename().string()), true);
		else
			newEntry = new File(new std::string(entry.path().filename().string()), true);

		directory->addEntry(newEntry);

		if (isDir)
			iterate((Directory*)newEntry);
	}
}
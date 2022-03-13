#include "log.h"
#include "indexer.h"
#include "indexerError.h"

#include <filesystem>

bool Indexer::isDirectory(std::string path, bool isCritical){
	FUN();

	std::error_code ec;
	bool isDir = std::filesystem::is_directory(path, ec);

	if (ec){
		if (isCritical && _failOnError)
			throw new IndexerError("FS error while checking " + path + ": " + ec.message());
		else{
			LOGW("WARNING: FS error while checking " + path + ": " + ec.message());
			return false;
		}
	}

	return isDir;
}

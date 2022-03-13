#include "log.h"
#include "indexer.h"
#include "indexerError.h"

#include <filesystem>

bool Indexer::isSymlink(std::string path, bool isCritical){
	FUN();

	std::error_code ec;
	bool isSym = std::filesystem::is_symlink(path, ec);

	if (ec){
		if (isCritical && _failOnError)
			throw new IndexerError("FS error while checking " + path + ": " + ec.message());
		else{
			LOGW("WARNING: FS error while checking " + path + ": " + ec.message());
			return false;
		}
	}

	return isSym;
}

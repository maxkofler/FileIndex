#include "log.h"
#include "indexer.h"
#include "indexerError.h"

#include <filesystem>
namespace fs = std::filesystem;

bool Indexer::index(std::string dir, bool failOnError){
	FUN();
	_failOnError = failOnError;

	{	//Check if the supplied path is a directory
		std::error_code ec;

		bool isDir = fs::is_directory(dir, ec);

		if (ec)
			throw new IndexerError("FS error when checking " + dir + ": " + ec.message());

		if (!isDir)
			throw new IndexerError("Path to index " + dir + " is not a directory");
	}

	std::error_code ec;

	fs::directory_entry rootDir(dir, ec);

	if (ec)
		throw new IndexerError("FS error when trying to access " + dir + ": " + ec.message());
	
	iterate(rootDir);

	return true;
}
#include "log.h"
#include "indexer.h"
#include "indexerError.h"

#include <filesystem>
namespace fs = std::filesystem;

bool Indexer::index(bool failOnError){
	FUN();
	_failOnError = failOnError;

	if (!isDirectory(_rootDir->getPathString()))
		throw new IndexerError("Can not index fs entry " + _rootDir->getPathString() + ": has to be a directory");

	iterate(_rootDir);

	return true;
}

/*
bool Indexer::index(bool failOnError){
	FUN();
	_failOnError = failOnError;

	std::string dir = _curDir->getPathString();

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
}*/
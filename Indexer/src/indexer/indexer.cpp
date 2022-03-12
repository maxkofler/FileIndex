#include "log.h"
#include "indexer.h"
#include "indexerError.h"

#include <filesystem>

namespace fs = std::filesystem;

Indexer::Indexer(Directory* rootDir){
	FUN();

	_rootDir = rootDir;
}


#include "log.h"
#include "indexer.h"
#include "indexerError.h"

#include <filesystem>

namespace fs = std::filesystem;

Indexer::Indexer(std::ostream& out) : _out(out){
	FUN();

	{	//Check if the output stream is ok
		if (!out.good())
			throw new IndexerError("Output stream is not good");
	}
}


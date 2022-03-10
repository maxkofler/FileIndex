#include "log.h"
#include "indexer.h"
#include "indexerError.h"

namespace fs = std::filesystem;

void Indexer::iterate(fs::directory_entry entry){
	FUN();

	bool isDir = false;

	{	//Check the directory entry
		std::error_code ec;

		isDir = fs::is_directory(entry, ec);

		if (ec){
			if (_failOnError){
				throw new IndexerError("FS error when checking " + entry.path().string() + ": " + ec.message());
			} else {
				LOGW("FS error when checking " + entry.path().string() + ": " + ec.message() + ", trying to continue...");
				return;
			}
		}
	}

	bool isLink = false;

	{	//Check if the entry is a symlink, skip it
		std::error_code ec;

		isLink = fs::is_symlink(entry, ec);

		if (ec){
			if (_failOnError){
				throw new IndexerError("FS error when checking " + entry.path().string() + ": " + ec.message());
			} else {
				LOGW("FS error when checking " + entry.path().string() + ": " + ec.message() + ", trying to continue...");
				return;
			}
		}
	}

	#ifdef DEBUG
	LOGF("Found entry: " + entry.path().string());
	#endif

	_entries.push_back(entry.path().string());

	//Skip link entries
	if (isLink){
		#ifdef DEBUG
		LOGD("Skipping symlink indexing of " + entry.path().string());
		#endif
		return;
	}

	if (isDir){
		std::error_code ec;
		for (fs::directory_entry newEntry : fs::directory_iterator(entry, ec)){
			if (ec){
				if (_failOnError) {
					throw new IndexerError("FS error while iterating " + entry.path().string() + ": " + ec.message());
				} else {
					LOGW("FS error while iterating " + entry.path().string() + ": " + ec.message() + " trying to continue...");
					break;
				}
			}

			iterate(newEntry);
		}
	}
}


#include "fileIndex.h"
#include "log.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

int main(int argc, char** argv){
	using namespace std::chrono;
	hlog = new Log::Log(Log::A);

	hlog->setFeature(Log::FEATURE_PRINTFUNNAMES, true);
	hlog->setFeature(Log::FEATURE_PROFILE, true);

	std::ofstream* outFile = new std::ofstream();
	outFile->open("trace.json", std::ios::out);
	hlog->setProfileStream(outFile);

	{
		FUN();

		if (argc != 2){
			LOGUE("Usage: ./fileindexcli <path to index>");
		}

		std::string rootName = argv[1];
		LOGU("Indexing \"" + rootName + "\"...");

		FileIndex index;

		fs_dir* root = new fs_dir;
		root->parent = nullptr;
		root->nameID = index.getDB()->add(rootName, root);

		auto indexStart = high_resolution_clock::now();
		index.index(root, rootName, true);
		auto indexStop = high_resolution_clock::now();
		auto indexDuration = duration_cast<milliseconds>(indexStop - indexStart);

		LOGD("Done indexing");
		LOGU("Optimizing...");

		auto optimizeStart = high_resolution_clock::now();
		index.optimizeDB();
		auto optimizeStop = high_resolution_clock::now();
		auto optimizeDuration = duration_cast<milliseconds>(optimizeStop - optimizeStart);

		LOGU(	"Done! " + std::to_string(index.getDB()->getEntriesCount()) + " entries in database, " + 
				std::to_string(index.getDB()->getBytesUsed()) + " bytes used");

		LOGU(	"Total entries indexed: " + std::to_string(index.getIndexedEntriesCount()));
		LOGU(	"Saved duplicated names: " + std::to_string(index.getSavedDuplicatesCount()));
		LOGU(	"Remaining names in DB: " + std::to_string(index.getDB()->getEntriesCount()));

		LOGU(	"Indexing took " + std::to_string(indexDuration.count()) + " ms");
		LOGU(	"Optimizing took " + std::to_string(optimizeDuration.count()) + " ms");

		bool run = true;
		std::string search;

		while(run){
			std::cout << ">>>";
			std::cin >> search;
			if (search.length() == 0)
				break;

			auto start = high_resolution_clock::now();
			auto res = index.getDB()->searchAll(search, false);

			std::sort(res.begin(), res.end(), [](const namesDB_searchRes &a, const namesDB_searchRes &b) -> bool {
				return a.matchRemaining > b.matchRemaining;
			});
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start);

			for (namesDB_searchRes entry : res){
				std::cout << "> " << NamesDB::getEntryName(entry.dbEntry) << std::endl;
			}

			std::cout << ">> " << res.size() << " hits in " << duration.count() << " ms" << std::endl;
		}
	}
	
	delete hlog;
	outFile->close();
	delete outFile;

}

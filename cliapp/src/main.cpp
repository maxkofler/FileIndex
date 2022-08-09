
#include "fileIndex.h"
#include "log.h"

#include <iostream>
#include <fstream>

int main(int argc, char** argv){
	hlog = new Log::Log(Log::F);

	hlog->setFeature(Log::FEATURE_PRINTFUNNAMES, false);
	hlog->setFeature(Log::FEATURE_PROFILE, true);

	FUN();

	std::ofstream* outFile = new std::ofstream();
	outFile->open("trace.json", std::ios::out);
	hlog->setProfileStream(outFile);

	if (argc != 2){
		LOGUE("Usage: ./fileindexcli <path to index>");
	}

	std::string rootName = argv[1];
	LOGU("Indexing \"" + rootName + "\"...");

	FileIndex index;

	fs_dir* root = new fs_dir;
	root->parent = nullptr;
	root->nameID = index.getDB()->add(rootName, root);

	index.index(root, rootName, true);

	LOGU(	"Done! " + std::to_string(index.getDB()->getEntriesCount()) + " entries in database, " + 
			std::to_string(index.getDB()->getBytesUsed()) + " bytes used");

	LOGU(	"Total entries indexed: " + std::to_string(index.getIndexedEntriesCount()));
	LOGU(	"Saved duplicated names: " + std::to_string(index.getSavedDuplicatesCount()));

	bool run = true;
	std::string search;

	while(run){
		std::cout << ">>>";
		std::cin >> search;
		if (search.length() == 0)
			break;

		auto res = index.getDB()->searchAll(search, false);

		for (namesDB_searchRes entry : res){
			std::cout << ">" << NamesDB::getEntryName(entry.dbEntry) << std::endl;
		}

		std::cout << ">> " << res.size() << " hits" << std::endl;
	}
	

}

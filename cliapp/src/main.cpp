
#include "fileIndex.h"
#include "log.h"

#include <iostream>
#include <fstream>

int main(int argc, char** argv){
	hlog = new Log::Log(Log::U);

	hlog->setFeature(Log::FEATURE_PRINTFUNNAMES, false);
	hlog->setFeature(Log::FEATURE_PROFILE, true);

	FUN();

	std::ofstream* outFile = new std::ofstream();
	outFile->open("trace.json", std::ios::out);
	hlog->setProfileStream(outFile);

	if (argc == 2){
		
		std::string rootName = argv[1];
		LOGU("Indexing \"" + rootName + "\"...");

		FileIndex index;

		fs_dir* root = new fs_dir;
		root->parent = nullptr;
		root->nameID = index.getDB()->add(rootName, root);

		index.index(root, rootName, true);

		LOGU(	"Done! " + std::to_string(index.getDB()->getEntriesCount()) + " entries in database, " + 
				std::to_string(index.getDB()->getBytesUsed()) + " bytes used");

		std::cin >> rootName;
		
	} else {
		LOGUE("Usage: ./fileindexcli <path to index>");
	}

}
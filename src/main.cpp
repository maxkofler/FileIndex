#include "mainwindow.h"

#include <QApplication>
#include <iostream>

#include <chrono>
#include <fstream>

#include "log.h"
#include "indexer.h"
#include "error.h"
#include "directory.h"
#include "file.h"

Log::Log* hlog;

int main(int argc, char *argv[]){
	hlog = new Log::Log(Log::MEM);
	hlog->setFeature(Log::FEATURE_PRINTFUNNAMES, false);

	using namespace std::chrono;
	
	if (argc != 2){
		LOGE("Expected 1 argument!");
		return -1;
	}

	try{
		FUN();

		std::string rootName(argv[1]);
		Directory root(&rootName);

		std::string in;
		std::cout << "Enter to proceed: ";
		std::cin >> in;

		{
			Indexer indexer(&root);

			auto start = high_resolution_clock::now();

			indexer.index(false);

			auto end = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(end - start);

			LOGI("Indexing took " + std::to_string(duration.count()) + " ms");
		}

		std::cout << "Enter to proceed: ";
		std::cin >> in;

		{//Now export the indexes
			auto entries = root.getRecursiveEntries();

			std::ofstream outFile;
			outFile.open("index.txt", std::ios::out);

			if (entries.size() != 0){
				FSEntry* last = &root;
				for(FSEntry* entry : entries){
					std::string path = last->getPathTo(entry);
					if (entry->type() == FS::ENTRY_DIRECTORY){
						path += '/';
						last = entry;
					}
					outFile << path << std::endl;
				}
			}
		}

	} catch (Error* e){
		LOGE("Failed: " + e->what());
	}
	
	delete hlog;
	return 0;

	/*QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();*/
}

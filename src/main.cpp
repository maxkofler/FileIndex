#include "mainwindow.h"

#include <QApplication>
#include <iostream>

#include <chrono>
#include <fstream>

#include "log.h"
#include "error.h"
#include "directory.h"
#include "file.h"

#include "fs.h"
#include "filesystem.h"

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
		std::string in;

		Filesystem fs(argv[1]);
		
		auto start = high_resolution_clock::now();
		fs.index(nullptr, true);
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);

		LOGI("Indexing took " + std::to_string(duration.count()) + " ms");
		LOGI("Holding " + std::to_string(fs.getEntryCount()) + " entries");
		LOGI("Requested names: " + std::to_string(fs.getNamesRequested()));
		LOGI("Allocated names: " + std::to_string(fs.getNamesAllocated()));
		LOGI("Name duplicates saved: " + std::to_string(fs.getDuplicateNamesSaved()));

		std::cout << "Enter to proceed: ";
		std::cin >> in;

		{
			std::ofstream outFile;
			outFile.open("index.txt", std::ios::out);
			fs.getRoot()->printRecursiveEntries(outFile);
			outFile.close();
		}

		{
			std::ofstream outFile;
			outFile.open("names.txt", std::ios::out);
			fs.printIndex(outFile);
			outFile.close();
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

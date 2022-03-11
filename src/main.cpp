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

		std::string childName = "child";
		Directory child(&childName);

		std::string fileName = "file";
		File file(&fileName);

		child.addEntry(&file);

		root.addEntry(&child);

		LOGD(file.getPathString());

		std::string in;
		std::cout << "Enter to proceed: ";
		std::cin >> in;

		Indexer indexer(&root);

		auto start = high_resolution_clock::now();

		indexer.index(false);

		auto end  = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);

		std::cout << "Indexing took " << duration.count() << " ms" << std::endl;
		std::cout << "Enter to proceed: ";
		std::cin >> in;

		std::string* newName = new std::string("NewName");
		Directory(newName, true);

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

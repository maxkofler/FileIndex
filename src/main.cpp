#include "mainwindow.h"

#include <QApplication>
#include <iostream>

#include <chrono>

#include "log.h"
#include "indexer.h"
#include "error.h"

Log::Log* hlog;

int main(int argc, char *argv[]){
	hlog = new Log::Log(Log::F);
	hlog->setFeature(Log::FEATURE_PRINTFUNNAMES, false);

	using namespace std::chrono;
	
	if (argc != 2){
		LOGE("Expected 1 argument!");
		return -1;
	}

	try{
		FUN();

		std::string in;
		std::cout << "Enter to proceed: ";
		std::cin >> in;

		Indexer indexer;

		auto start = high_resolution_clock::now();

		indexer.index(argv[1], false);

		auto end  = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);

		std::cout << "Indexing took " << duration.count() << " ms" << std::endl;
		std::cout << "Enter to proceed: ";
		std::cin >> in;

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

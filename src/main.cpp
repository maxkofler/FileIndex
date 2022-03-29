#include <QApplication>
#include <iostream>

#include <chrono>
#include <fstream>

#include "log.h"
#include "error.h"

#include "namesDB.h"

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
		
		auto start = high_resolution_clock::now();
		
		//Do something
		NamesDB db;

		for (int i = 0; i < 1000; i++){
			db.createName("name" + std::to_string(i));
		}

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);

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

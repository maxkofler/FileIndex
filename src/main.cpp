#include "mainwindow.h"

#include <QApplication>

#include "log.h"
#include "indexer.h"

Log::Log* hlog;

int main(int argc, char *argv[]){
	hlog = new Log::Log(Log::FUNCALLS);
	hlog->setFeature(Log::FEATURE_PRINTFUNNAMES, false);
	
	{//The real main starts here
		FUN();

		Indexer indexer;
	}
	
	delete hlog;
	return 0;

	/*QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();*/
}


//#include "fileIndexOld.h"
#define FRIEND_FS
#include "fileIndex.h"
#include "fs.h"
#include "log.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

#include <filesystem>

int main(int argc, char** argv){
    using namespace std::chrono;
    hlog = new Log::Log(Log::F);

    hlog->setFeature(Log::FEATURE_PRINTFUNNAMES, false);
    hlog->setFeature(Log::FEATURE_PROFILE, true);

    std::ofstream* outFile = new std::ofstream();
    outFile->open("trace.json", std::ios::out);
    hlog->setProfileStream(outFile);

    {
        FUN();

        NamesDB fsDB("FS-main");
        FS fs(&fsDB, false);
        FileIndex fileIndex(&fs);

        if (std::filesystem::exists("db.bin")){
            LOGU("Importing existing database...");

            std::ifstream dbFile;
            dbFile.open("db.bin", std::ios::binary | std::ios::in);

            if (!fsDB.importDB(dbFile)){
                LOGUE("Failed to import DB, renamed it to <name>.corrupted");
                std::filesystem::rename("db.bin", "db.bin.corrupted");
            }

            dbFile.close();
        } else if (argc != 2){
            LOGUE("Usage: ./fileindexcli <path to index>");
        } else {
            std::string rootName = argv[1];
            LOGU("Indexing \"" + rootName + "\"...");

            auto indexStart = high_resolution_clock::now();
            fileIndex.index(rootName, true);
            auto indexStop = high_resolution_clock::now();
            auto indexDuration = duration_cast<milliseconds>(indexStop - indexStart);

            LOGD("Done indexing");
            LOGU("Optimizing...");

            auto optimizeStart = high_resolution_clock::now();
            //fileIndex.optimizeDB();
            auto optimizeStop = high_resolution_clock::now();
            auto optimizeDuration = duration_cast<milliseconds>(optimizeStop - optimizeStart);

            LOGU(	"Storing database...");
            {
                std::ofstream dbFile;
                dbFile.open("db.bin", std::ios::binary | std::ios::out);

                fsDB.exportDB(dbFile);

                dbFile.close();
            }

            LOGU(	"Indexing took " + std::to_string(indexDuration.count()) + " ms");
            LOGU(	"Optimizing took " + std::to_string(optimizeDuration.count()) + " ms");
        }

        

        LOGU(	"Done! " + std::to_string(fsDB.getEntriesCount()) + " entries in database, " + 
                std::to_string(fsDB.getBytesUsed()) + " bytes used");

        //LOGU(	"Total entries indexed: " + std::to_string(index.getIndexedEntriesCount()));
        //LOGU(	"Saved duplicated names: " + std::to_string(index.getSavedDuplicatesCount()));
        //LOGU(	"Remaining names in DB: " + std::to_string(index.getDB()->getEntriesCount()));

        bool run = true;
        std::string search;

        while(run){
            std::cout << ">>>";
            std::cin >> search;
            if (feof(stdin))
                break;

            auto start = high_resolution_clock::now();
            auto res = fsDB.searchAll(search, false);
            auto stop = high_resolution_clock::now();
            auto searchDuration = duration_cast<milliseconds>(stop - start);

            start = high_resolution_clock::now();
            std::sort(res.begin(), res.end(), [](const namesDB_searchRes &a, const namesDB_searchRes &b) -> bool {
                return a.matchRemaining > b.matchRemaining;
            });
            stop = high_resolution_clock::now();
            auto sortDuration = duration_cast<milliseconds>(stop - start);
            

            for (namesDB_searchRes entry : res){
                std::cout << " > " << fs.getEntryPathString((size_t)entry.data) << std::endl;
            }

            std::cout << ">> " << res.size() << " hits in " << searchDuration.count() << " ms ("  << sortDuration.count() << " ms sorting)" << std::endl;
        }
    }
    
    delete hlog;
    outFile->close();
    delete outFile;

}

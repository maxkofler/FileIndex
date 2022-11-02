
//#include "fileIndexOld.h"
#define FRIEND_FS
#include "log.h"
#include "fileIndex.h"
#include "fs.h"

#include "config.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

#include <filesystem>

int main(int argc, char** argv){
    using namespace std::chrono;
    hlog = new Log::Log(Log::U);

    hlog->setFeature(Log::FEATURE_PRINTFUNNAMES, false);
    hlog->setFeature(Log::FEATURE_PROFILE, true);

    std::ofstream* outFile = new std::ofstream();
    outFile->open("trace.json", std::ios::out);
    hlog->setProfileStream(outFile);

    config_t conf = parseFromCLI(argc, argv);
    if (!conf.ok)
        return -1;
    applyConfig(conf);

    {
        FUN();

        NamesDB<fs_entry> fsDB("FS-main");
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

            if (!fs.importFS(dbFile)){
                LOGUE("Failed to import FS, renamed it to <name>.corrupted");
                std::filesystem::rename("db.bin", "db.bin.corrupted");
            }

            dbFile.close();
        } else {
            //std::string rootName = argv[1];
            std::string rootName = conf.indexPath;
            LOGU("Indexing \"" + rootName + "\"...");

            auto indexStart = high_resolution_clock::now();
            fileIndex.index(rootName, true);
            auto indexStop = high_resolution_clock::now();
            auto indexDuration = duration_cast<milliseconds>(indexStop - indexStart);

            LOGD("Done indexing");

            LOGU(	"Storing database...");
            {
                std::ofstream dbFile;
                dbFile.open("db.bin", std::ios::binary | std::ios::out);

                fsDB.exportDB(dbFile);
                fs.exportFS(dbFile);

                dbFile.close();
            }

            LOGU(	"Indexing took " + std::to_string(indexDuration.count()) + " ms");
        }

        fsDB.updateIndex();

        LOGU(	"Done! " + std::to_string(fsDB.getEntriesCount()) + " entries in database, " + 
                std::to_string(fsDB.getBytesUsed()) + " bytes used");

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
            std::sort(res.begin(), res.end(), [](const namesDB_searchRes<fs_entry> &a, const namesDB_searchRes<fs_entry> &b) -> bool {
                return a.matchRemaining > b.matchRemaining;
            });
            stop = high_resolution_clock::now();
            auto sortDuration = duration_cast<milliseconds>(stop - start);

            std::string pathStr;
            for (namesDB_searchRes entry : res){
                pathStr = fs.getEntryPathString(entry.id);
                std::cout << fsDB.getName(entry.data->nameID) << " (" << pathStr << ")" << std::endl;
            }

            std::cout << ">> " << res.size() << " hits in " << searchDuration.count() << " ms ("  << sortDuration.count() << " ms sorting)" << std::endl;
        }
    }
    
    delete hlog;
    outFile->close();
    delete outFile;

}

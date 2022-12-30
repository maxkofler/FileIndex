
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

        FS fs;
        FileIndex fileIndex(&fs);

        std::string rootName = conf.indexPath;
        LOGU("Indexing \"" + rootName + "\"...");

        auto indexStart = high_resolution_clock::now();
        fileIndex.index(rootName, true, "fsroot");
        auto indexStop = high_resolution_clock::now();
        auto indexDuration = duration_cast<milliseconds>(indexStop - indexStart);

        LOGD("Done indexing");

        LOGU("Indexing took " + std::to_string(indexDuration.count()) + " ms");

        bool run = true;
        std::string search;

        while(run){
            std::cout << ">>>";
            std::cin >> search;
            if (feof(stdin))
                break;

            /*
            auto start = high_resolution_clock::now();
            auto res = fsDB.searchAll(search, false, false);
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
            */
        }
    }
    
    delete hlog;
    outFile->close();
    delete outFile;

}

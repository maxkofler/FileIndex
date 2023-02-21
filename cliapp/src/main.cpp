
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

        SQL sql(conf.databasePath);
        FS fs(sql);
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

            auto start = high_resolution_clock::now();
            auto res = fs.search(search);
            auto stop = high_resolution_clock::now();
            auto searchDuration = duration_cast<milliseconds>(stop - start);

            for(fs_entry entry : res){
                std::cout << fs.getPathString(entry) << std::endl;
            }

            std::cout << ">> " << res.size() << " hits in " << searchDuration.count() << "ms" << std::endl;
        }
    }
    
    delete hlog;
    outFile->close();
    delete outFile;

}

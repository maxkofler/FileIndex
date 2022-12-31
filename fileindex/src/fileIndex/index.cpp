#include "log.h"
#include "fileIndex.h"

#include <filesystem>

size_t FileIndex::index(std::string pathStr, bool recursive, std::string crateStr){
    FUN();

    namespace fs = std::filesystem;
    std::error_code ec;

    //Check if the path even exists
    bool exists = fs::exists(pathStr, ec);
    if (ec){
        LOGUE("[FileIndex][index] Failed to check path \"" + pathStr + "\": " + ec.message());
        return 0;
    }

    if (!exists){
        LOGUE("[FileIndex][index] Path to index \"" + pathStr + "\" does not exist");
        return 0;
    }

    //Check if the path is a directory
    bool isDir = fs::is_directory(pathStr, ec);
    if (ec){
        LOGUE("[FileIndex][index] Failed to check path \"" + pathStr + "\": " + ec.message());
        return 0;
    }

    if (!isDir){
        LOGUE("[FileIndex][index] Path to index \"" + pathStr + "\" is not a directory");
        return 0;
    }

    if (crateStr.empty())
        crateStr = pathStr;

    fs_dir d;
    d.name = crateStr;
    d.parentID = 0;

    //Disable foreign keys for adding the root, the parentID is 0 and a foreign key would fail
    _fs->getSQL().exec("PRAGMA foreign_keys = OFF;");
    add(d);
    _fs->getSQL().exec("PRAGMA foreign_keys = ON;");

    LOGD("[FileIndex][index] Indexing " + pathStr + " into crate " + crateStr);

    index_blind(pathStr, d, recursive);

    return _indexedEntries;
}

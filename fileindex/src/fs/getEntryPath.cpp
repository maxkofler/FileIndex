#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests

void FS::getEntryPath(size_t entryID, std::deque<fs_entry>& path){
    FUN();
    DEBUG_EX("FS::getEntryPath()");

    if (entryID >= _entries.size())
        return;

    auto entry = _entries._data[entryID];

    if (entry.parentID != 0) {
        getEntryPath(entry.parentID, path);
    }
    path.push_back(entry);
}

std::string FS::getEntryPathString(size_t entryID){
    FUN();
    DEBUG_EX("FS::getEntryPathString()");

    std::string pathStr;

    if (entryID >= _entries.size())
        return pathStr;

    std::deque<fs_entry> path;
    getEntryPath(entryID, path);

    for (fs_entry& entry : path){
        pathStr += _db->getName(entry.nameID) + '/';
    }

    pathStr.erase(pathStr.length()-1);

    return pathStr;
}

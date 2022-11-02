#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests

void FS::getEntryPath(size_t entryID, std::deque<fs_entry>& path){
    FUN();
    DEBUG_EX("FS::getEntryPath()");

    fs_entry* entry = _db->getEntry(entryID);
    if (entry == nullptr)
        return;

    if (entry->parentID != 0) {
        getEntryPath(entry->parentID, path);
    }

    path.push_back(*entry);
}

std::string FS::getEntryPathString(size_t entryID){
    FUN();
    DEBUG_EX("FS::getEntryPathString()");

    std::string pathStr;

    if (entryID >= _db->getEntriesCount())
        return pathStr;

    std::deque<fs_entry> path;
    getEntryPath(entryID, path);

    for (fs_entry& entry : path){
        pathStr += _db->getName(entry.nameID) + '/';
    }

    if (pathStr.length() > 0)
        pathStr.erase(pathStr.length()-1);

    return pathStr;
}

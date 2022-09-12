#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests

std::deque<fs_entry> FS::getEntryPath(size_t entryID){
    FUN();
    DEBUG_EX("FS::getEntryPath()");

    std::deque<fs_entry> path;

    if (entryID >= _entries.size())
        return path;

    fs_entry* curEntry = &_entries._data[entryID];
    path.push_front(*curEntry);
    size_t nextEntryID = curEntry->parentID;

    while(nextEntryID != 0){
        curEntry = &_entries._data[nextEntryID];
        path.push_front(*curEntry);
        size_t nextEntryID = curEntry->parentID;
    }

    path.push_front(_entries._data[0]);

    return path;
}

std::string FS::getEntryPathString(size_t entryID){
    FUN();
    DEBUG_EX("FS::getEntryPathString()");

    std::string pathStr;

    if (entryID >= _entries.size())
        return pathStr;

    auto path = getEntryPath(entryID);

    for (fs_entry& entry : path){
        pathStr += _db->getEntryName(_db->getDBEntry(entry.nameID)) + '/';
    }

    pathStr.erase(pathStr.length()-1);

    return pathStr;
}

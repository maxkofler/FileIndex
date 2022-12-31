#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests

std::deque<fs_entry> FS::getPath(fs_entry& entry){
    FUN();

    std::deque<fs_entry> ret;

    fs_entry curEntry = entry;

    while (curEntry.parentID != 0){
        ret.push_front(curEntry);

        curEntry = getEntryByID(curEntry.parentID);
        if (curEntry.id == 0)
            break;
    }

    return ret;
}

std::string FS::getPathString(fs_entry& entry){
    FUN();

    std::string ret;
    std::deque<fs_entry> entries = getPath(entry);

    for (fs_entry e : entries)
        ret += e.name + "/";

    //Remove trailing '/'
    if (ret.length() > 0)
        ret = ret.replace(ret.length()-1, 1, "");

    return ret;
}

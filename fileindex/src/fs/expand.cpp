#include "log.h"
#include "debug.h"

#include "fs.h"

#include <cstring>

//TODO: Tests

void FS::expand(size_t amount){
    FUN();
    DEBUG_EX("FS::expand()");

    if (amount == 0)
        amount = _chunkSize;

    size_t newSize = _size_entries + amount;

    fs_entry* newArray = new fs_entry[newSize];

    std::memcpy(newArray, _entries, _size_entries*sizeof(fs_entry));

    delete _entries;

    _entries = newArray;
    _size_entries = newSize;
}

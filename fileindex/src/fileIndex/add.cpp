#include "log.h"
#include "debug.h"

#include "fileIndex.h"

bool FileIndex::add(fs_entry& entry){
    FUN();

    return _fs->add(entry);
}

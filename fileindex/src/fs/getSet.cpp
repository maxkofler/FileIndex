#include "log.h"
#include "debug.h"

#include "fs.h"

NamesDB<fs_entry>* FS::getDB(){
    return _db;
}

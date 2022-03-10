#include "log.h"
#include "directory.h"

FS::entry_type Directory::type(){
	return FS::ENTRY_DIRECTORY;
}

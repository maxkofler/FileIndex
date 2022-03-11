#include "log.h"
#include "directory.h"

Directory::Directory(std::string* name, bool owns) : FSEntry(name, owns){
	FUN();
}

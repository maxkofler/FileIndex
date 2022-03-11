#include "log.h"
#include "file.h"

File::File(std::string* name, bool owns) : FSEntry(name, owns){
	FUN();
}

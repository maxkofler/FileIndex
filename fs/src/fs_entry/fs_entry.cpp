#include "log.h"
#include "fs_entry.h"

FSEntry::FSEntry(fs_name name) : _name(name){
	FUN();
}

FSEntry::~FSEntry(){
	FUN();
}
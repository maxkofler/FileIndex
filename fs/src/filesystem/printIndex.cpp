#include "log.h"
#include "filesystem.h"
#include "fsError.h"

void Filesystem::printIndex(std::ostream& stream){
	FUN();

	if (stream.bad())
		throw new FSError("Output stream is bad");

	//TODO: output the index
}

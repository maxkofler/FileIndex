#define FRIEND_NAMES_DB

#include "log.h"
#include "fileIndex.h"

size_t FileIndex::optimizeDB(){
	FUN();

	_db->clean();

	#warning This function (FileIndex::optimizeDB()) is not complete!

	return 0;
}

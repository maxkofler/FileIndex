#ifndef __FILEINDEX_H__
#define __FILEINDEX_H__

#include "namesDB.h"
#include "fstypes.h"

class FileIndex{

public:
	FileIndex(NamesDB* db = nullptr);
	~FileIndex();

#ifndef FRIEND_FILEINDEX
private:
#endif

	NamesDB*			_db = nullptr;
	bool				_externalDB = false;

};

#endif

#include "../t_fileIndex.h"

TEST(FileIndex, FSEntry_Structs){
	FUN();

	fs_dir dir;
	fs_file file;

	ASSERT_TRUE(dir.isDir);
	ASSERT_FALSE(file.isDir);

	//Now try casting them around to check for SEGFAULTS
	
	fs_entry* dirP = &dir;
	fs_entry* fileP = &file;

	ASSERT_TRUE(dirP->isDir);
	ASSERT_FALSE(fileP->isDir);

}
